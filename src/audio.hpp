// File: audio.hpp
#ifndef DRUMPI_AUDIO_H
#define DRUMPI_AUDIO_H

#include <vector>
#include <string>
#include <memory>

#include <jack/jack.h>

#include "defs.hpp"

namespace drumpi {
namespace audio {

/*! Abstract sample retieval callback class. */
class AudioCallback {
    public:
        virtual std::vector<sample_t> getSamples(int nSamples) = 0;
};

/*! Audio engine class for interacting with the JACK server. */
class JackClient {
    public:
        /*! Constructor.
        Specifies parameters to JACK.
        \param clientName requested client name in JACK.
        \param nOutPorts number of output ports. Default 2.
        \param nInPorts number of input ports. Default 0. */
        JackClient(std::string clientName, int nOutPorts = JackClient::defNumOutPorts, int nInPorts = JackClient::defNumInPorts);

        /*! Informs JACK that the program is ready to go.
        \param callback `AudioCallback` type object to fetch output samples.
        \return error code. */
        audioError_t start(AudioCallback& callback);

        /*! Stops the JACK engine.
        \param closeClient whether to close the client or just 'deactivate' it.
        \return error code. */
        audioError_t stop(bool closeClient = true);

        /*! Read method to send output buffer to the JACK server.
        Called by JACK when samples are needed.
        \param nFrames number of frames requested by JACK.
        \param arg pointer to the `PlaybackEngine` object being used.
        \return JACK error code */
        static int _process(jack_nframes_t nFrames, void *arg);

        /*! Shutdown method to exit the program should the JACK server shut down or disconnect the client.
        \param arg zero/null. */
        static void _shutdown(void *arg);
    
    private:
        /*! Pointer to the callback object that fetches output samples. */
        AudioCallback* callback;

        /*! Sets the number of JACK ports.
        \param nOutPorts number of output ports.
        \param nInPorts number of input ports. */
        void setNumPorts(int nOutPorts, int nInPorts);

        /*! Default number of output ports. */
        static const int defNumOutPorts = 2;
        /*! Default number of input ports. */
        static const int defNumInPorts = 0;

        /*! Pointer to the JACK client. */
        jack_client_t *client;
        /*! JACK client name. */
        std::string clientName;
        /*! JACK output ports. */
        std::vector<jack_port_t*> outPorts;
        /*! JACK input ports. Not (yet) implemented. */
        std::vector<jack_port_t*> inPorts;
        /*! JACK ports string. */
        std::vector<std::string> ports;
        /*! JACK options. */
        jack_options_t options = JackNullOption;
        /*! JACK status. */
        jack_status_t jackStatus;

        /*! JackClient error state. */
        audioError_t errorStatus = NO_ERROR;
};

} // namespace audio
} // namespace drumpi

#endif // define DRUMPI_AUDIO_H