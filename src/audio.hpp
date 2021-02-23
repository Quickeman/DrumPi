// File: audio.hpp
#ifndef DRUMPI_AUDIO_H
#define DRUMPI_AUDIO_H

#include <vector>
#include <string>

#include <jack/jack.h>

namespace drumpi {
namespace audio {

/*! Sample data format used by JACK (`float`). */
typedef jack_default_audio_sample_t SAMPLE_FORMAT;

/*! Audio driver class for interacting with the JACK server. */
class AudioEngine {
    public:
        /*! Constructor.
        Sets up the connection to the JACK server. */
        AudioEngine();

        /*! Setup method.
        Used to specify parameters to JACK.
        \param clientName requested client name in JACK.
        \param serverName requested server name in JACK. `NULL` by default.
        \return error code, zero means no error. */
        int setup(std::string clientName, std::string serverName = NULL);

        /*! Informs JACK that the program is ready to go.
        \param _callback pointer to a callback function to collect samples. */
        void start(std::vector<SAMPLE_FORMAT> (*_callback)(int));

        /*! Read method to send output buffer to the JACK server.
        Called by JACK when samples are needed.
        \param nFrames number of frames requested by JACK.
        \param arg */
        int _read(jack_nframes_t nFrames, void *arg);

        /*! Shutdown method to exit the program should the JACK server shut down or disconnect the client. */
        void _shutdown(void *arg);
    
    private:
        /*! Pointer to callback function for fetching samples. */
        std::vector<SAMPLE_FORMAT> (*_callback)(int);

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

} // namespace audio
} // namespace drumpi

#endif // define DRUMPI_AUDIO_H