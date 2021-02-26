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
namespace engine {

/*! Abstract sample retieval callback class. */
class AudioCallback {
    public:
        virtual std::vector<sample_t> getSamples(int nSamples) = 0;
};

/*! Audio engine class for interacting with the JACK server. */
class AudioEngine {
    public:
        /*! Default constructor. */
        AudioEngine();

        /*! Constructor that specifies a number of ports. 
        \param nOutPorts number of output ports. Default 2.
        \param nInPorts number of input ports. Default 0. */
        AudioEngine(int nOutPorts, int nInPorts);

        /*! Setup method.
        Used to specify parameters to JACK.
        \param callback `AudioCallback` type object to fetch output samples.
        \param clientName requested client name in JACK.
        \param serverName requested server name in JACK. Blank by default.
        \return error code, zero means no error. */
        audioError_t setup(AudioCallback& callback, std::string clientName);

        /*! Informs JACK that the program is ready to go.
        \return error code. */
        audioError_t start();

        /*! Stops the JACK engine.
        \return error code. */
        audioError_t stop();

        /*! Read method to send output buffer to the JACK server.
        Called by JACK when samples are needed.
        \param nFrames number of frames requested by JACK.
        \param arg pointer to the `PlaybackEngine` object being used. */
        static int _process(jack_nframes_t nFrames, void *arg);

        /*! Shutdown method to exit the program should the JACK server shut down or disconnect the client. */
        static void _shutdown(void *arg);
    
    private:
        /*! Pointer to the callback object that fetches output samples. */
        AudioCallback* callback;

        /*! Default number of output ports. */
        static const int defNumOutPorts = 2;
        /*! Default number of input ports. */
        static const int defNumInPorts = 0;
        /*! Sets the number of output ports */
        void setNumPorts(int nOutPorts = defNumOutPorts, int nInPorts = defNumInPorts);

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
        jack_status_t status;
};

} // namespace engine
} // namespace audio
} // namespace drumpi

#endif // define DRUMPI_AUDIO_H