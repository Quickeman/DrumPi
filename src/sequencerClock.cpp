#include "sequencerClock.hpp"

using namespace drumpi;

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