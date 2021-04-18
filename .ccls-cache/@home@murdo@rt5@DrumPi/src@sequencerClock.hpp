#ifndef SEQUENCER_CLOCK_H
#define SEQUENCER_CLOCK_H

#include <memory>

#include "sequencer.hpp"
#include "clock.hpp"

namespace drumpi {

/*! \ref Metronome derived class to clock a \ref Sequencer. */
class SequencerClock : public clock::Metronome {
    public:
        /*! Constructor. */
        SequencerClock();

        /*! Sets the Sequencer to be clocked.
        \param s \ref Sequencer object to be clocked. */
        void setSequencer(std::shared_ptr<Sequencer> s);

        /*! Override the tick method.
        Clocks the \ref Sequencer given to \ref setSequencer. */
        void tick() override;
    
    private:
        /*! Pointer to the `Sequencer` object to be clocked. */
        std::shared_ptr<Sequencer> seq = nullptr;
};

} // namespace drumpi

#endif // define SEQUENCER_CLOCK_H