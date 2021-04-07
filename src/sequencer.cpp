// File: sequencer.cpp

#include <memory>

#include "sequencer.hpp"

using namespace drumpi;

// _SequenceStep class

_SequenceStep::_SequenceStep() {
    clear();
}

void _SequenceStep::add(drumID_t id) {
    switches[id] = true;
}

void _SequenceStep::remove(drumID_t id) {
    switches[id] = false;
}

void _SequenceStep::toggle(drumID_t id) {
    switches[id] = !switches[id];
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
    active.reserve(NUM_DRUMS);
    for (int i = 0; i < switches.size(); i++) {
        if (isActive((drumID_t)i)) {
            active.push_back((drumID_t)i);
        }
    }
    active.shrink_to_fit();
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
    stepNum = -1;
    if (clearSteps) clear();
}

void Sequencer::add(drumID_t drum, int step) {
    steps[step].add(drum);
}

void Sequencer::add(drumID_t drum) {
    add(drum, stepNum);
}

void Sequencer::remove(drumID_t drum, int step) {
    steps[step].remove(drum);
}

void Sequencer::remove(drumID_t drum) {
    remove(drum, stepNum);
}

void Sequencer::toggle(drumID_t drum, int step) {
    steps[step].toggle(drum);
}

void Sequencer::toggle(drumID_t drum) {
    toggle(drum, stepNum);
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

SequencerClock::SequencerClock(std::shared_ptr<Sequencer> s, audio::PlaybackEngine& p) {
    setRateBPM(480);
    rateChangeFlag = false;

    seq = s;
    pbe = &p;
}

void SequencerClock::tick() {
    seq->step();

    std::vector<drumID_t> active = seq->getActive();
    for(int i = 0; i < active.size(); i++) pbe->trigger(active[i]);
}