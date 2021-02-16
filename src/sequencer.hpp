// File: sequencer.hpp
#pragma once
#include <vector>
#include "clock.hpp"

namespace sequencer {

#ifndef SEQUENCER_H
#define SEQUENCER_H

#ifndef NUM_DRUMS
#define NUM_DRUMS 8
#endif // define NUM_DRUMS

/*! Step class for a Sequencer object. */
class Step {
    public:
        /*! Step constructor. */
        Step();

        /*! Adds the sample with the passed ID to the step.
        \param id ID of the drum to be added. */
        void addToStep(int id);

        /*! Removes the sample with the passed ID from the step.
        \param id ID of the drum to be removed. */
        void removeFromStep(int id);

        /*! Returns true if the sample with the passed ID is active in the step.
        \param id ID of the drum to be tested. */
        bool isActive(int id);

        /*! Get the number of active drums in the step.
        \return The number of active drums. */
        int numActive();

        /*! Returns a vector of the active drums' IDs.
        \return A vector containing the IDs of the active drums. */
        std::vector<int> getActive();

        /*! Removes all drums from the Step. */
        void clear();
    
    private:
        /*! Container for drum trigger switches. */
        bool switches[NUM_DRUMS];
};


class Sequencer {
    public:
        /*! Defualt constructor. */
        Sequencer();
        /*! Sequencer constructor.
        \param numSteps the number of steps in the sequence. */
        Sequencer(const int numSteps);

        /*! Advance the sequencer by one step.
        Updates tracking and sends relevant samples to output. */
        void advance();

        /*! Get the current step number.
        \return The current step number. */
        int getStepNum();

        /*! Starts the sequencer.
        If already running, resets playhead to beginning of sequence. */
        void start();

        /*! Sets the clock rate in BPM.
        \param bpm the desired clocking rate in beats per minute (BPM). */
        void setRate_bpm(int bpm);
        /*! Sets the clock rate in miliseconds.
        \param ms the desired clocking rate in miliseconds. */
        void setRate_ms(int ms);

        /*! Clear sequence pattern. */
        void clear();

        /*! Resets the sequencer to initial conditions.
        \param clearSteps whether to clear the sequence pattern. */
        void reset(bool clearSteps = true);
    
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

        /*! Clock object to trigger the sequencer. */
        Clock clock;

        /*! True if sequencer is running. */
        bool running;
};

#endif // define SEQUENCER_H

} // namespace sequencer