#include "sampleSource.hpp"

#include <AudioFile.h>

using namespace drumpi;
using namespace audio;

SampleSource::SampleSource() {
    status = SOURCE_ERROR;
    type = SOURCE_GENERALISED;
}

sampleSourceStatus_t SampleSource::getStatus() {
    return status;
}

sampleSourceType_t SampleSource::getType() {
    return type;
}


// class AudioClip

AudioClip::AudioClip(std::string filepath) {
    type = SOURCE_PREGENERATED;
    loadFile(filepath);

    numSamples = clip.size();

    reset();
}

std::vector<sample_t> AudioClip::getSamples(int nSamples) {
    std::vector<sample_t> b(nSamples);
    bool endFlag = false;
    // Number of samples to copy
    int nSamplesCopy = nSamples;

    status = SOURCE_ACTIVE;
    
    if ((playhead + nSamples) >= numSamples) { // If the playhead will overrun...
        endFlag = true;
        nSamplesCopy = samplesRemaining();
    }

    for (int i = 0; i < nSamplesCopy; i++) {
        // Copy samples from clip
        b[i] = clip[playhead];
        playhead++;
    }

    for (int i = nSamplesCopy; i < nSamples; i++) {
        // Fill remainder of buffer with zeros if needed
        b[i] = 0.f;
    }

    if (endFlag) status = SOURCE_FINISHED;

    return b;
}

void AudioClip::reset() {
    playhead = 0;
    updateStatus();
}

void AudioClip::updateStatus() {
    if (clip.empty()) {
        status = SOURCE_ERROR;
        return;
    }

    if (playhead == 0) {
        status = SOURCE_READY;
    } else if (playhead > 0) {
        status = SOURCE_ACTIVE;
    } else if (playhead >= numSamples) {
        status = SOURCE_FINISHED;
    } else {
        status = SOURCE_ERROR;
    }
}

void AudioClip::hardReset() {
    loadFile(filepath);
    reset();
}

void AudioClip::loadFile(std::string filepath) {
    AudioFile<sample_t> file;
    bool loaded;
    
    this->filepath = filepath;

    status = SOURCE_LOADING;

    file.shouldLogErrorsToConsole(false);
    loaded = file.load(this->filepath);

    if (!loaded) {
        status = SOURCE_ERROR;
        return;
    }

    clip = file.samples[0];
    numSamples = clip.size();
    status = SOURCE_READY;
}

int AudioClip::samplesRemaining() {
    return numSamples - playhead;
}