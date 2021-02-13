// File: audio.hpp
#include <sound/asound.h>

namespace audio {

#ifndef audio_h
#define audio_h

class AudioDriver {
    public:
        /** Audio driver class constructor
         */
        AudioDriver();

        /** Audio driver class destructor
         */
        ~AudioDriver();

        /** Thread-safe running method
         */
        int run();

        /** Audio format
         */
        struct AudioFormat {
            int bufferSize = 64;
            int sampleRate = 48000; //Hz
        } format;
    
    private:
        bool running = false;
};

#endif // define audio_h

} // namespace audio