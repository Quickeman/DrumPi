#include "sequencerClock.hpp"

using namespace drumpi;

SequencerClock::SequencerClock() {
    setRateBPM(240);
    rateChangeFlag = false;
}

void SequencerClock::setSequencer(Sequencer* s) {
    seq.reset(s);
}

void SequencerClock::tick() {
    seq->step();
}