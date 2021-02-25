// File: audio.cpp
#include <iostream>

#include <audio.hpp>

using namespace drumpi;
using namespace audio;
using namespace engine;

AudioEngine::AudioEngine() {
    setNumPorts();
}

AudioEngine::AudioEngine(int nOutPorts, int nInPorts) {
    setNumPorts(nOutPorts, nInPorts);
}

AudioEngine::~AudioEngine() {
    audioError_t err = stop();

    if (err) exit(1);
}

audioError_t AudioEngine::setup(AudioCallback& callback, std::string clientName, std::string serverName) {
    // Establish client and server names
    this->clientName = clientName;
    if (serverName != "") {
        this->serverName = serverName;
        int setupOptions = JackNullOption | JackServerName;
        options = (jack_options_t)setupOptions;
    }

    // Open a client connection to the JACK server
    client = jack_client_open(
        this->clientName.data(), 
        options, 
        &status, 
        this->serverName.data()
    );
    // Client opening errors
    if (client == NULL) {
        if (status & JackServerFailed) {
            return SERVER_CONNECT_FAILED;
        }
        return CLIENT_OPEN_FAILED;
    }

    // Non-unique name given
    if (status & JackNameNotUnique) this->clientName = jack_get_client_name(client);

    // Set up callback
    this->callback = &callback;
    jack_set_process_callback(client, _process, this);

    // Set up shutdown routine
    jack_on_shutdown(client, _shutdown, 0);

    // Create the ports
    // Outputs
    for (int i = 0; i < outPorts.size(); i++) {
        std::string name = "output";
        name = name.append(std::to_string(i + 1));
        outPorts[i] = jack_port_register(
            client,
            name.data(),
            JACK_DEFAULT_AUDIO_TYPE,
            JackPortIsOutput,
            0
        );

        // No available ports error
        if (outPorts[i] == NULL) {
            return NO_PORTS_AVAILABLE;
        }
    }

    return NO_ERROR;
}

audioError_t AudioEngine::start() {
    audioError_t retErr = NO_ERROR;
    // Activate JACK client
    int err = jack_activate(client);
    // Error handling
    if (err) {
        return CLIENT_ACTIVATE_FAILED;
    }

    // Get port names(?)
    // Ports are input as they are 'input' to the backend
    const char **portsTemp = jack_get_ports(client, NULL, NULL, JackPortIsPhysical|JackPortIsInput);
    for (int i = 0; i < ports.size(); i++) {
        ports[i] = portsTemp[i];
        err = jack_connect(
            client,
            jack_port_name(outPorts[i]), 
            ports[i].data()
        );
        if (err) {
            retErr = PORT_CONNECT_FAILED;
        }
    }

    jack_free(portsTemp);

    return retErr;
}

audioError_t AudioEngine::stop() {
    int err = jack_client_close(client);

    if (err) return CLIENT_CLOSE_ERROR;

    return NO_ERROR;
}

int AudioEngine::_process(jack_nframes_t nFrames, void *arg) {
    // `arg` should be a pointer to the AudioEngine object
    AudioEngine* self = static_cast<AudioEngine*>(arg);
    // Vector of pointers to sample buffers
    // Not 2D vector as `jack_port_get_buffer` returns a pointer, not values
    std::vector<sample_t*> out(self->outPorts.size());
    std::vector<sample_t> samples(nFrames);

    samples = self->callback->getSamples(nFrames);

    for (int i = 0; i < out.size(); i++) {
        // Get a sample memory buffer for each port
        out[i] = static_cast<sample_t*>(
            jack_port_get_buffer(self->outPorts[i], nFrames)
        );

        for (int j = 0; j < nFrames; j++) {
            out[i][j] = samples[j];
        }
    }

    return NO_ERROR;
}

void AudioEngine::_shutdown(void *arg) {
    // If JACK calls this, close the program.
    exit(1);
}

void AudioEngine::setNumPorts(int nOutPorts, int nInPorts) {
    outPorts.resize(nOutPorts);
    inPorts.resize(nInPorts);
    ports.resize(nOutPorts + nInPorts);
}