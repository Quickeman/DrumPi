// File: sequencer.cpp

#include "sequencer.hpp"

namespace sequencer {

// Sequencer class

Sequencer::Sequencer(const int numSteps) {
    this->numSteps = numSteps;
    steps.resize(this->numSteps);
    stepNum = -1;
    updateStep();
}

void Sequencer::advance() {
    // Update Sequencer state
    updateStep();

    // Instruct Sampler to output sounds
    //TODO
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

int Sequencer::getCurrentStep() {
    return stepNum;
}


// Step class

} // namespace sequencer