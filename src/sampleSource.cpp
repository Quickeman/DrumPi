#include "sampleSource.hpp"

using namespace drumpi;
using namespace audio;

SampleSource::SampleSource() {

}

sampleSourceStatus_t SampleSource::getStatus() {
    return status;
}

sampleSourceType_t SampleSource::getType() {
    return type;
}


AudioClip::AudioClip(std::string filepath) {

}

std::vector<sample_t> AudioClip::getSamples(int nSamples) {
    std::vector<sample_t> b;
    return b;
}

void AudioClip::reset() {

}

void AudioClip::updateStatus() {
    
}

void AudioClip::hardReset() {

}

void AudioClip::loadFile() {

}

int AudioClip::samplesRemaining() {
    return 0;
}