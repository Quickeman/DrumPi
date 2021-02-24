// File: audio.cpp
#include <audio.hpp>

using namespace drumpi;
using namespace audio;
using namespace engine;

AudioEngine::AudioEngine() {

}

int AudioEngine::setup(PlaybackEngine<SAMPLE_FORMAT>& pbe, std::string clientName, std::string serverName) {
    return -1;
}

int AudioEngine::start() {
    return -1;
}

int AudioEngine::stop() {
    return -1;
}

int AudioEngine::_process(jack_nframes_t nFrames, void *arg) {
    return -1;
}

void AudioEngine::_shutdown(void *arg) {

}