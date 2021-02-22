// File: audio.hpp
#ifndef DRUMPI_AUDIO_H
#define DRUMPI_AUDIO_H

#include <jack/jack.h>
#include <vector>

namespace drumpi {
namespace audio {

/*! Audio driver class for interacting with the JACK server. */
class JackDriver {
    public:
        /*! Constructor.
        Sets up the connection to the JACK server. */
        JackDriver();

        /*! Setup method.
        Used to specify parameters to JACK. */
        int setup();

        /*! Informs JACK that the program is ready to go. */
        void start();

        /*! Read method to send output buffer to the JACK server.
        Called by JACK when samples are needed. */
        int read(jack_nframes_t numFrames, void *arg);

        /*! Shutdown method to exit the program should the JACK server shut down or disconnect the client. */
        void shutdown(void *arg);

        /*! Send samples to the output buffer.
        \param samples a vector of the samples to be sent to the output. 2D to allow for non-monophonic output. */
        int toOutput(std::vector<std::vector<jack_default_audio_sample_t>> samples);
    
    private:
        /*! Output sample buffer. */
        std::vector<std::vector<jack_default_audio_sample_t>> buffer;
};


/*! Audio driver class specifically for use with the DrumPi. Higher-level than JackDriver. */
class AudioDriver {
    public:
        /*! Constructor. */
        AudioDriver();

    private:
        /*! JackDriver object. */
        JackDriver jackD;
};

} // namespace audio
} // namespace drumpi

#endif // define DRUMPI_AUDIO_H