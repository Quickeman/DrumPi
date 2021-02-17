// File: sequencer.hpp
#pragma once
#include <vector>

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
        \param n number of step to advance by. */
        void step(int n = 1);

        /*! Returns the active samples' IDs for the current step.
        \return A vector containing the IDs of the active drums. */
        std::vector<int> getActive();

        /*! Returns the whole sequencer pattern.
        \return A 2D vector of the Sequencer pattern. */
        std::vector<std::vector<bool>> getSequence();

        /*! Get the current step number.
        \return The current step number. */
        int getStepNum();

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
        /*! Call to update the active step pointer.
        Should be called after the active step ID is updated. */
        void _updateStepPtr();
};

#endif // define SEQUENCER_H

} // namespace sequencer
