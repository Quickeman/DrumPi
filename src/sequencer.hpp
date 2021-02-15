// File: sequencer.hpp
#pragma once
#include <vector>
#include "clock.hpp"

namespace sequencer {

#ifndef sequencer_h
#define sequencer_h

#ifndef NUM_DRUMS
#define NUM_DRUMS 8
#endif // define NUM_DRUMS

/*! Step class for a Sequencer object. */
class Step {
    public:
        /*! Step constructor. */
        Step();

        /*! Adds the sample with the passed ID to the step. */
        void addToStep(int id);

        /*! Removes the sample with the passed ID from the step. */
        void removeFromStep(int id);

        /*! Returns true if the sample with the passed ID is active in the step. */
        bool isActive(int id);

        /*! Returns the number of active samples in step. */
        int numActive();

        /*! Returns a vector of the active drums' IDs. */
        std::vector<int> getActive();
    
    private:
        /*! Container for drum trigger switches. */
        bool switches[NUM_DRUMS];
};


class Sequencer {
    public:
        /*! Defualt constructor. */
        Sequencer();
        /*! Sequencer constructor. */
        Sequencer(const int numSteps);

        /*! Advance the sequencer by one step.
        Updates tracking and sends relevant samples to output. */
        void advance();

        /*! Returns the current step number. */
        int getCurrentStep();

        /*! Starts the sequencer.
        If already running, resets playhead to beginning of sequence. */
        void start();

        /*! Sets the clock rate in BPM. */
        void setRate_bpm(int bpm);
        /*! Sets the clock rate in miliseconds. */
        void setRate_ms(int time);
    
    private:
        /*! Container for step objects. */
        std::vector<Step> steps;
        /*! Number of steps in the sequence. */
        int numSteps;

        /*! ID of the current step.
        Index in the `steps` array. */
        int stepNum;
        /*! Call to update the active step ID. */
        void _updateStepID();

        /*! Pointer to currently active step object. */
        Step* currentStep;
        /*! Call to update the active step pointer. */
        void _updateStepPtr();

        /*! Updates both the active step ID and pointer. */
        void updateStep();

        Clock clock;
};

#endif // define sequencer_h

} // namespace sequencer