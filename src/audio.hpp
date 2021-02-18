// File: audio.hpp
#ifndef AUDIO_H
#define AUDIO_H

#include <jack/jack.h>
#include <vector>

namespace audio {

/*! Audio driver class for interacting with jackd. */
class AudioDriver {
    public:
        /*! Audio driver class constructor. */
        AudioDriver();

        /*! Read method to send output buffer to jackd. */
        int read();

        /*! Audio format. */
        struct AudioFormat {
            /*! Output buffer length in samples. */
            int bufferSize = 64;
            /*! Driver sample rate. */
            int sampleRate = 48000; //Hz
        } format;
    
    private:
        /*! Output sample buffer. */
        std::vector<int> buffer;
};

} // namespace audio

#endif // define AUDIO_H