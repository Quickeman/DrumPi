#include "playback.hpp"
#include "math.h"

using namespace drumpi;
using namespace audio;

PlaybackEngine::PlaybackEngine() {
    masterVol = masterVolDef;

    for (int i = 0; i < NUM_DRUMS; i++) {
        isTriggered[i] = false;
        volumes[i] = volumeDef;
    }

    // Calculate volume lookup table
    for (int i = 0; i < volumeTable.size(); i++) {
        float x = float(i) / 100.f;
        volumeTable[i] = x * powf(10.f, x - 1.f);
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
            float vol = volumeTable[masterVol] * volumeTable[volumes[i]];
            for (int j = 0; j < nSamples; j++) {
                buffer[j] += temp[j] * vol;
            }

            // Check source status
            // If finished, untrigger the source
            if (sources[i]->getStatus() == SOURCE_FINISHED) untrigger((drumID_t)i);
        }
    }

    return buffer;
}

void PlaybackEngine::trigger(drumID_t drum) {
    if (sources[drum]->getStatus() == SOURCE_ACTIVE) sources[drum]->reset();
    isTriggered[drum] = true;
}

void PlaybackEngine::untrigger(drumID_t drum) {
    isTriggered[drum] = false;
    sources[drum]->reset();
}

std::vector<drumID_t> PlaybackEngine::getActive() {
    std::vector<drumID_t> v;
    v.reserve(NUM_DRUMS);
    for (int i = 0; i < NUM_DRUMS; i++) {
        if (isTriggered[i]) v.push_back((drumID_t)i);
    }
    v.shrink_to_fit();
    return v;
}

void PlaybackEngine::volumeUp(drumID_t drum) {
    volumes[drum] = std::min(volumes[drum] + volumeStep, 100);
}

void PlaybackEngine::volumeUp() {
    masterVol = std::min(masterVol + volumeStep, 100);
}

void PlaybackEngine::volumeDown(drumID_t drum) {
    volumes[drum] = std::max(volumes[drum] - volumeStep, 0);
}

void PlaybackEngine::volumeDown() {
    masterVol = std::max(masterVol - volumeStep, 0);
}

int PlaybackEngine::getVolume(drumID_t drum) {
    return volumes[drum];
}

int PlaybackEngine::getVolume() {
    return masterVol;
}

sampleSourceStatus_t PlaybackEngine::loadBank(int bank, sampleSourceType_t type) {
    sampleSourceStatus_t status, retStat;
    retStat = SOURCE_READY;

    for(int i = 0; i < NUM_DRUMS; i++) {
        status = setSource((drumID_t)i, bank, type);
        if (status != SOURCE_READY) retStat = status;
    }

    return retStat;
}

sampleSourceStatus_t PlaybackEngine::setSource(drumID_t drum, int bank, sampleSourceType_t type) {
    sampleSourceStatus_t status;

    switch (type) {
        case SOURCE_GENERALISED:
        default:
            status = SOURCE_ERROR;
            break;
        
        case SOURCE_PREGENERATED:
            sources[drum].reset(new AudioClip(library.getFilepath(drum, bank, type)));
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