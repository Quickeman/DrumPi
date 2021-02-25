#include "sampleSource.hpp"

using namespace drumpi;
using namespace audio;

SampleSource::SampleSource() {

}

sampleSourceType_t SampleSource::getType() {
    return SOURCE_GENERALISED;
}


AudioClip::AudioClip() {

}

AudioClip::AudioClip(std::string filepath) {

}

std::vector<sample_t> AudioClip::getSamples(int nSamples) {
    std::vector<sample_t> b;
    return b;
}

void AudioClip::reset() {

}

sampleSourceStatus_t AudioClip::getStatus() {
    return SOURCE_ERROR;
}

void AudioClip::hardReset() {

}

void AudioClip::loadFile() {

}

int AudioClip::samplesRemaining() {
    return 0;
}