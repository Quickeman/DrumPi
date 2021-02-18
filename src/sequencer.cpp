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
}

void Sequencer::step(int n) {
    for (int i = 0; i < n; i++) {
        _updateStepID();
        _updateStepPtr();
    }
}

std::vector<int> Sequencer::getActive() {
    return currentStep->getActive();
}

std::vector<std::vector<bool>> Sequencer::getSequence() {
    std::vector<std::vector<bool>> pattern;
    pattern.resize(numSteps);
    for (int i = 0; i < numSteps; i++) {
        // For each Step...
        pattern[i].resize(NUM_DRUMS);
        for (int j = 0; j < NUM_DRUMS; j++) {
            // For each drum...
            pattern[i][j] = steps[i].isActive(j);
        }
    }
    return pattern;
}

int Sequencer::getStepNum() {
    return stepNum;
}

void Sequencer::clear() {
    for (int i = 0; i < numSteps; i++) {
        steps[i].clear();
    }
}

void Sequencer::reset(bool clearSteps) {
    stepNum = -1;
    step();
    if (clearSteps) clear();
}

void Sequencer::_updateStepID() {
    stepNum++;
    if (stepNum >= numSteps) stepNum = 0;
}

void Sequencer::_updateStepPtr() {
    currentStep = &steps[stepNum];
}

} // namespace sequencer