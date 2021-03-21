#ifndef SEQUENCER_CLOCK_H
#define SEQUENCER_CLOCK_H

#include "sequencer.hpp"
#include "clock.hpp"

namespace drumpi {

class SequencerClock : public clock::Metronome {
    public:
        /*! Sets the Sequencer object to be clocked. */
        void setSequencer(sequencer::Sequencer& s);

        /*! Override the tick method. */
        void tick() override;
    
    private:
        /*! Pointer to the `Sequencer` object to be clocked. */
        sequencer::Sequencer* seq;
};

} // namespace drumpi

#endif // define SEQUENCER_CLOCK_H
