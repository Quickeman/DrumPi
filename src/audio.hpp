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
        /*! Constructor. */
        AudioEngine();

        /*! Destructor.
        Closes the JACK client. */
        ~AudioEngine();

        /*! Setup method.
        Used to specify parameters to JACK.
        \param callback `AudioCallback` type object to fetch output samples.
        \param clientName requested client name in JACK.
        \param serverName requested server name in JACK. `NULL` by default.
        \return error code, zero means no error. */
        int setup(AudioCallback& callback, std::string clientName, std::string serverName = NULL);

        /*! Informs JACK that the program is ready to go.
        \return error code. */
        int start();

        /*! Stops the JACK engine.
        \return error code. */
        int stop();

        /*! Read method to send output buffer to the JACK server.
        Called by JACK when samples are needed.
        \param nFrames number of frames requested by JACK.
        \param arg pointer to the `PlaybackEngine` object being used. */
        static int _process(jack_nframes_t nFrames, void *arg);

        /*! Shutdown method to exit the program should the JACK server shut down or disconnect the client. */
        static void _shutdown(void *arg);
    
    private:
        AudioCallback* callback;

        /*! Pointer to the JACK client. */
        jack_client_t *client;
        /*! JACK client name. */
        std::string clientName;
        /*! JACK server name. */
        std::string serverName;
        /*! JACK ports. */
        std::vector<jack_port_t*> outPorts;
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