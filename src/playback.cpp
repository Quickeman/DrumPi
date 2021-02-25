#include "playback.hpp"

using namespace drumpi;
using namespace audio;
using namespace engine;

PlaybackEngine::PlaybackEngine() {

}

std::vector<sample_t> PlaybackEngine::getSamples(int nSamples) {
    std::vector<sample_t> b;
    return b;
}

void PlaybackEngine::trigger(drumID_t id) {

}

std::vector<drumID_t> PlaybackEngine::getActive() {
    std::vector<drumID_t> v;
    return v;
}

void PlaybackEngine::untrigger(drumID_t id) {

}