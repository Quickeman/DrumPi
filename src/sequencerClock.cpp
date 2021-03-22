#include "sequencerClock.hpp"

using namespace drumpi;

void SequencerClock::setSequencer(Sequencer& s) {
    *seq = s;
}

void SequencerClock::tick() {
    return;
}