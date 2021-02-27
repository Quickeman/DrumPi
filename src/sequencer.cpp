// File: sequencer.cpp

#include "sequencer.hpp"

using namespace drumpi;
using namespace sequencer;

// Step class

Step::Step() {
    switches.resize(NUM_DRUMS);
    clear();
}

void Step::addToStep(drumID_t id) {
    switches[id] = true;
}

void Step::removeFromStep(drumID_t id) {
    switches[id] = false;
}

bool Step::isActive(drumID_t id) {
    return switches[id];
}

int Step::numActive() {
    int n = 0;
    for (int i = 0; i < switches.size(); i++) {
        n += (int)switches[i];
    }
    return n;
}

std::vector<drumID_t> Step::getActive() {
    std::vector<drumID_t> active;
    for (int i = 0; i < switches.size(); i++) {
        if (isActive((drumID_t)i)) {
            active.push_back((drumID_t)i);
        }
    }
    return active;
}

void Step::clear() {
    for (int i = 0; i < switches.size(); i++) {
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

bool Sequencer::isActive(drumID_t drum, int step) {
    return steps[step].isActive(drum);
}

bool Sequencer::isActive(drumID_t drum) {
    return isActive(drum, stepNum);
}

std::vector<drumID_t> Sequencer::getActive() {
    return currentStep->getActive();
}

std::vector<bool> Sequencer::getSteps(drumID_t drumID) {
    std::vector<bool> v(numSteps);
    for (int i = 0; i < numSteps; i++) {
        v[i] = steps[i].isActive(drumID);
    }
    return v;
}

std::vector<std::vector<bool>> Sequencer::getSequence() {
    std::vector<std::vector<bool>> pattern;
    pattern.resize(numSteps);
    for (int i = 0; i < numSteps; i++) {
        // For each Step...
        pattern[i].resize(NUM_DRUMS);
        for (int j = 0; j < NUM_DRUMS; j++) {
            // For each drum...
            pattern[i][j] = steps[i].isActive((drumID_t)j);
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

void Sequencer::addToStep(drumID_t drum, int step) {
    steps[step].addToStep(drum);
}

void Sequencer::addToStep(drumID_t drum) {
    addToStep(drum, stepNum);
}

void Sequencer::removeFromStep(drumID_t drum, int step) {
    steps[step].removeFromStep(drum);
}

void Sequencer::removeFromStep(drumID_t drum) {
    removeFromStep(drum, stepNum);
}

void Sequencer::_updateStepID() {
    stepNum++;
    if (stepNum >= numSteps) stepNum = 0;
}

void Sequencer::_updateStepPtr() {
    currentStep = &steps[stepNum];
}