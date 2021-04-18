// File: audio.cpp
#include <audio.hpp>

using namespace drumpi;
using namespace audio;

JackClient::JackClient(std::string clientName, int nOutPorts, int nInPorts) {
    open = false;
    running = false;

    setNumPorts(nOutPorts, nInPorts);

    // Establish client name
    this->clientName = clientName;

    // Open a client connection to the Jack server
    client = jack_client_open(
        clientName.data(),
        options,
        &jackStatus
    );
    // Client opening errors
    if (client == NULL) {
        if (jackStatus & JackServerFailed) {
            errorStatus = SERVER_CONNECT_FAILED;
        }
        errorStatus = CLIENT_OPEN_FAILED;
    } else {
        open = true;
    }

    // Non-unique name given
    if (jackStatus & JackNameNotUnique) clientName.assign(jack_get_client_name(client));

    // Set up shutdown routine
    jack_on_shutdown(client, JackClient::_shutdown, 0);

    // Create the ports
    // Outputs
    for (int i = 0; i < outPorts.size(); i++) {
        std::string name = "output";
        name.append(std::to_string(i + 1));
        outPorts[i] = jack_port_register(
            client,
            name.data(),
            JACK_DEFAULT_AUDIO_TYPE,
            JackPortIsOutput,
            0
        );

        // No available ports error
        if (outPorts[i] == NULL) {
            errorStatus = NO_PORTS_AVAILABLE;
        }
    }
}

JackClient::~JackClient() {
    if (running) jack_deactivate(client);
    if (open) jack_client_close(client);
}

audioError_t JackClient::start(AudioCallback& callback) {
    // Establish if any errors occurred in setup routine (in constructor)
    if (errorStatus != NO_ERROR) {
        return errorStatus;
    }

    // Set up callback
    this->callback = &callback;
    jack_set_process_callback(client, JackClient::_process, this);

    // Activate Jack client
    int err = jack_activate(client);
    // Error handling
    if (err) {
        return CLIENT_ACTIVATE_FAILED;
    } else{
        running = true;
    }

    // Get port names(?)
    // Output ports are inputs as they are 'input' to the backend
    const char** portsTemp = jack_get_ports(client, NULL, NULL, JackPortIsPhysical|JackPortIsInput);
    for (int i = 0; i < ports.size(); i++) {
        ports[i] = portsTemp[i];
        err = jack_connect(
            client,
            jack_port_name(outPorts[i]), 
            ports[i].data()
        );
        if (err) {
            errorStatus = PORT_CONNECT_FAILED;
        }
    }

    jack_free(portsTemp);

    return errorStatus;
}

audioError_t JackClient::stop(bool closeClient) {
    int err;

    if (closeClient) {
        err = jack_client_close(client);
        if (err) return CLIENT_CLOSE_ERROR;
        running = false;
        open = false;
    } else {
        err = jack_deactivate(client);
        if (err) return CLIENT_DEACTIVATE_ERROR;
        running = false;
    }

    return NO_ERROR;
}

bool JackClient::isOpen() {
    return open;
}

bool JackClient::isRunning() {
    return running;
}

int JackClient::_process(jack_nframes_t nFrames, void *arg) {
    // `arg` should be a pointer to the JackClient object
    JackClient* self = static_cast<JackClient*>(arg);
    // Vector of pointers to sample buffers
    // Not 2D vector as `jack_port_get_buffer` returns a pointer, not values
    std::vector<sample_t*> out(self->outPorts.size());
    std::vector<sample_t> samples(nFrames);

    samples = self->callback->getSamples(nFrames);

    for (int i = 0; i < out.size(); i++) { // For each port...
        // Get a sample memory buffer for each port
        out[i] = (sample_t*)jack_port_get_buffer(self->outPorts[i], nFrames);

        for (int j = 0; j < nFrames; j++) { // For each frame/sample...
            // Copy retrieved samples to output
            out[i][j] = samples[j];
        }
    }

    return NO_ERROR;
}

void JackClient::_shutdown(void *arg) {
    // If Jack calls this, close the program.
    exit(1);
}

void JackClient::setNumPorts(int nOutPorts, int nInPorts) {
    outPorts.resize(nOutPorts);
    inPorts.resize(nInPorts);
    ports.resize(nOutPorts + nInPorts);
}
