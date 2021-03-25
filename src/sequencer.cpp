// File: sequencer.cpp

#include <memory>

#include "sequencer.hpp"

using namespace drumpi;

// _SequenceStep class

_SequenceStep::_SequenceStep() {
    switches.resize(NUM_DRUMS);
    clear();
}

void _SequenceStep::addToStep(drumID_t id) {
    switches[id] = true;
}

void _SequenceStep::removeFromStep(drumID_t id) {
    switches[id] = false;
}

bool _SequenceStep::isActive(drumID_t id) {
    return switches[id];
}

int _SequenceStep::numActive() {
    int n = 0;
    for (int i = 0; i < switches.size(); i++) {
        n += (int)switches[i];
    }
    return n;
}

std::vector<drumID_t> _SequenceStep::getActive() {
    std::vector<drumID_t> active;
    for (int i = 0; i < switches.size(); i++) {
        if (isActive((drumID_t)i)) {
            active.push_back((drumID_t)i);
        }
    }
    return active;
}

void _SequenceStep::clear() {
    for (int i = 0; i < switches.size(); i++) {
        switches[i] = false;
    }
}


// Sequencer class

Sequencer::Sequencer(const int numSteps) {
    setNumSteps(numSteps);
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
        // For each _SequenceStep...
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

void Sequencer::setNumSteps(int n) {
    numSteps = n;
    steps.resize(numSteps);
}

void Sequencer::_updateStepID() {
    stepNum++;
    if (stepNum >= numSteps) stepNum = 0;
}

void Sequencer::_updateStepPtr() {
    currentStep = &steps[stepNum];
}


// SequencerClock class

SequencerClock::SequencerClock() {
    setRateBPM(240);
    rateChangeFlag = false;
}

void SequencerClock::setSequencer(std::shared_ptr<Sequencer> s) {
    seq = s;
}

void SequencerClock::tick() {
    seq->step();
}