// File: sequencer.hpp
#ifndef SEQUENCER_H
#define SEQUENCER_H

#include "defs.hpp"

#include <vector>

namespace drumpi {
namespace sequencer {

/*! Step class for a Sequencer object. */
class Step {
    public:
        /*! Step constructor. */
        Step();

        /*! Adds the sample with the passed ID to the step.
        \param id ID of the drum to be added. */
        void addToStep(drumID_t id);

        /*! Removes the sample with the passed ID from the step.
        \param id ID of the drum to be removed. */
        void removeFromStep(drumID_t id);

        /*! Returns true if the sample with the passed ID is active in the step.
        \param id ID of the drum to be tested. */
        bool isActive(drumID_t id);

        /*! Get the number of active drums in the step.
        \return The number of active drums. */
        int numActive();

        /*! Returns a vector of the active drums' IDs.
        \return A vector containing the IDs of the active drums. */
        std::vector<drumID_t> getActive();

        /*! Removes all drums from the Step. */
        void clear();
    
    private:
        /*! Container for drum trigger switches. */
        std::vector<bool> switches;
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

        /*! Returns `true` if the specified drum is active in the specified step.
        \param drum ID of the drum to test.
        \param step ID of the step to test. */
        bool isActive(drumID_t drum, int step);

        /*! Returns `true` if the specified drum is active in the current step.
        \param drum ID of the drum to test. */
        bool isActive(drumID_t drum);

        /*! Returns the active samples' IDs for the current step.
        \return A vector containing the IDs of the active drums. */
        std::vector<drumID_t> getActive();

        /*! Returns a series of switches for the specified drum's presence in each step.
        \param drumID ID of the drum to check.
        \return a vector of bools, true if the drum is active in that index's step. */
        std::vector<bool> getSteps(drumID_t drumID);

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

        /*! Adds the specified drum to the specified step.
        \param drum ID of the drum to add.
        \param step ID of the step to be modified. */
        void addToStep(drumID_t drum, int step);

        /*! Adds the specified drum to the current step.
        \param drum ID of the drum to add. */
        void addToStep(drumID_t drum);

        /*! Removes the specified drum from the specified step.
        \param drum ID of the drum to remove.
        \param step ID of the step to be modified. */
        void removeFromStep(drumID_t drum, int step);

        /*! Removes the specified drum from the current step.
        \param drum ID of the drum to remove. */
        void removeFromStep(drumID_t drum);
    
    private:
        /*! Container for step objects. */
        std::vector<Step> steps;
        /*! Number of steps in the sequence. */
        int numSteps;

        /*! ID of the current step.
        Index in the `steps` vector. */
        int stepNum;
        /*! Call to update the active step ID. */
        void _updateStepID();

        /*! Pointer to currently active step object. */
        Step* currentStep;
        /*! Call to update the active step pointer.
        Should be called after the active step ID is updated. */
        void _updateStepPtr();
};

} // namespace sequencer
} // namespace drumpi

#endif // define SEQUENCER_H