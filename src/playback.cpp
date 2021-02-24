#include "playback.hpp"

using namespace drumpi;
using namespace audio;
using namespace engine;

template<typename T>
PlaybackEngine<T>::PlaybackEngine() {

}

template<typename T>
std::vector<T> PlaybackEngine<T>::getSamples(int nSamples) {
    std::vector<T> b;
    return b;
}

template<typename T>
void PlaybackEngine<T>::trigger(drumID_t id) {

}

template<typename T>
void PlaybackEngine<T>::untrigger(drumID_t id) {

}