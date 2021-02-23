#include "sampleSource.hpp"

using namespace drumpi;
using namespace audio;

template<typename T>
SampleSource<T>::SampleSource() {

}

template<typename T>
sampleSourceType_t SampleSource<T>::getType() {

}


template<typename T>
AudioClip<T>::AudioClip(std::string filepath) {

}

template<typename T>
std::vector<T> AudioClip<T>::getSamples(int nSamples) {

}

template<typename T>
void AudioClip<T>::reset() {

}

template<typename T>
sampleSourceStatus_t AudioClip<T>::getStatus() {

}

template<typename T>
void AudioClip<T>::hardReset() {

}

template<typename T>
void AudioClip<T>::loadFile() {

}

template<typename T>
int AudioClip<T>::samplesRemaining() {

}