#include "playback.hpp"

using namespace drumpi;
using namespace audio;

PlaybackEngine::PlaybackEngine() {
    sources.resize(NUM_DRUMS);
    isTriggered.resize(NUM_DRUMS);
    volumes.resize(NUM_DRUMS);

    masterVol = masterVolDef;

    for (int i = 0; i < NUM_DRUMS; i++) {
        isTriggered[i] = false;
        volumes[i] = volumeDef;
    }
}

std::vector<sample_t> PlaybackEngine::getSamples(int nSamples) {
    // Create temporary buffer for source returns
    std::vector<sample_t> temp(nSamples);

    // Clear object buffer and set the size
    buffer.clear();
    buffer.resize(nSamples);

    for (int i = 0; i < NUM_DRUMS; i++) { // For each drum...
        if (isTriggered[i]) {
            // Get samples from the source
            temp = sources[i]->getSamples(nSamples);

            // Copy additively into object buffer
            // Take volumes into account at this stage
            for (int j = 0; j < nSamples; j++) {
                buffer[j] += temp[j] * masterVol * volumes[i];
            }

            // Check source status
            // If finished, untrigger the source
            if (sources[i]->getStatus() == SOURCE_FINISHED) untrigger((drumID_t)i);
        }
    }

    return buffer;
}

void PlaybackEngine::trigger(drumID_t drum) {
    isTriggered[drum] = true;
}

void PlaybackEngine::untrigger(drumID_t drum) {
    isTriggered[drum] = false;
    sources[drum]->reset();
}

std::vector<drumID_t> PlaybackEngine::getActive() {
    std::vector<drumID_t> v;
    for (int i = 0; i < NUM_DRUMS; i++) {
        if (isTriggered[i]) v.push_back((drumID_t)i);
    }
    return v;
}

void PlaybackEngine::setVolume(float volume, drumID_t drum) {
    volumes[drum] = volume;
}

void PlaybackEngine::setVolume(float volume) {
    masterVol = volume;
}

float PlaybackEngine::getVolume(drumID_t drum) {
    return volumes[drum];
}

float PlaybackEngine::getVolume() {
    return masterVol;
}

sampleSourceStatus_t PlaybackEngine::setSource(drumID_t drum, sampleSourceType_t type) {
    sampleSourceStatus_t status;

    switch (type) {
        case SOURCE_GENERALISED:
        default:
            status = SOURCE_ERROR;
            break;
        
        case SOURCE_PREGENERATED:
            // sources[drum].reset(new AudioClip(filepath));
            sources[drum].reset(new AudioClip(library.getFilepath(drum, type)));
            status = sources[drum]->getStatus();
            break;
    }

    return status;
}

sampleSourceStatus_t PlaybackEngine::getSourceStatus(drumID_t drum) {
    return sources[drum]->getStatus();
}

sampleSourceType_t PlaybackEngine::getSourceType(drumID_t drum) {
    return sources[drum]->getType();
}