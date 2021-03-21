#include "sequencerClock.hpp"

using namespace drumpi;

void SequencerClock::setSequencer(sequencer::Sequencer& s) {
    *seq = s;
}

void SequencerClock::tick() {
    return;
}