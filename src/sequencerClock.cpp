#include "sequencerClock.hpp"

using namespace drumpi;

SequencerClock::SequencerClock(Sequencer& s) {
    *seq = s;
}

void SequencerClock::tick() {
    seq->step();
}