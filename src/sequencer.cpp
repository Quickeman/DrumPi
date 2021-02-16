// File: sequencer.cpp

#include "sequencer.hpp"

namespace sequencer {

// Step class

Step::Step() {
    clear();
}

void Step::addToStep(int id) {
    switches[id] = true;
}

void Step::removeFromStep(int id) {
    switches[id] = false;
}

bool Step::isActive(int id) {
    return switches[id];
}

int Step::numActive() {
    int n = 0;
    for (int i = 0; i < NUM_DRUMS; i++) {
        n += (int)switches[i];
    }
    return n;
}

std::vector<int> Step::getActive() {
    std::vector<int> active;
    for (int i = 0; i < NUM_DRUMS; i++) {
        if (isActive(i)) {
            active.push_back(i);
        }
    }
    return active;
}

void Step::clear() {
    for (int i = 0; i < NUM_DRUMS; i++) {
        switches[i] = false;
    }
}


// Sequencer class

Sequencer::Sequencer(const int numSteps) {
    this->numSteps = numSteps;
    steps.resize(this->numSteps);
    reset();
    running = false;
}

void Sequencer::advance() {
    // Update Sequencer state
    updateStep();

    // Instruct Sampler to output sounds
    // TODO
}

int Sequencer::getStepNum() {
    return stepNum;
}

void Sequencer::start() {
    if (!running) {
        // clock.start()
        running = true;
    } else {
        // clock.stop() ?
        reset(false);
        // clock.start() ?
    }
}

void Sequencer::setRate_bpm(int bpm) {
    setRate_ms(bpmToMs(bpm));
}

void Sequencer::setRate_ms(int ms) {
    // clock.stop()
    // clock.start(ms)
}

void Sequencer::clear() {
    for (int i = 0; i < numSteps; i++) {
        steps[i].clear();
    }
}

void Sequencer::reset(bool clearSteps = true) {
    stepNum = -1;
    updateStep();
    if (clearSteps) clear();
}

void Sequencer::_updateStepID() {
    stepNum++;
    if (stepNum >= numSteps) stepNum = 0;
}

void Sequencer::_updateStepPtr() {
    currentStep = &steps[stepNum];
}

void Sequencer::updateStep() {
    _updateStepID();
    _updateStepPtr();
}

} // namespace sequencer