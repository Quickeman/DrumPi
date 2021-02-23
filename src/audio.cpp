// File: audio.cpp
#include <audio.hpp>

using namespace drumpi;
using namespace audio;

AudioEngine::AudioEngine() {

}

int AudioEngine::setup(std::string clientName, std::string serverName) {

}

void AudioEngine::start(std::vector<SAMPLE_FORMAT> (*_callback)(int)) {

}

int AudioEngine::_read(jack_nframes_t nFrames, void *arg) {

}

void AudioEngine::_shutdown(void *arg) {
    
}