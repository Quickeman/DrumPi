// File: sequencer.hpp
#ifndef SEQUENCER_H
#define SEQUENCER_H

#include "defs.hpp"
#include "clock.hpp"
#include "playback.hpp"

#include <vector>
#include <array>

namespace drumpi {

/*! Step class for a \ref Sequencer object. */
class _SequenceStep {
    public:
        /*! _SequenceStep constructor. */
        _SequenceStep();

        /*! Adds the drum with the passed \ref drumID_t to the step.
        \param id \ref drumID_t of the drum to be added. */
        void add(drumID_t id);

        /*! Removes the drum with the passed \ref drumID_t from the step.
        \param id \ref drumID_t of the drum to be removed. */
        void remove(drumID_t id);

        /*! Toggles the drum with the passed \ref drumID_t in the step.
        \param id \ref drumID_t of the drum to be toggled. */
        void toggle(drumID_t id);

        /*! Returns true if the drum with the passed \ref drumID_t is active in
        the step.
        \param id \ref drumID_t of the drum to be tested. */
        bool isActive(drumID_t id);

        /*! Get the number of active drums in the step.
        \return the number of active drums. */
        int numActive();

        /*! Returns a vector of the active drums' \ref drumID_t.
        \return a vector containing the \ref drumID_t of the active drums. */
        std::vector<drumID_t> getActive();

        /*! Removes all drums from the \ref _SequenceStep. */
        void clear();
    
    private:
        /*! Container for drum trigger switches. */
        std::array<bool, NUM_DRUMS> switches;
};


class Sequencer {
    public:
        /*! Constructor.
        \param numSteps the number of steps in the sequence. */
        Sequencer(const int numSteps);

        /*! Advance the \ref Sequencer by one step.
        \param n number of step(s) to advance by. */
        void step(int n = 1);

        /*! Returns `true` if the specified drum is active in the specified step.
        \param drum \ref drumID_t of the drum to test.
        \param step ID of the step to test. */
        bool isActive(drumID_t drum, int step);

        /*! Returns `true` if the specified drum is active in the current step.
        \param drum \ref drumID_t of the drum to test. */
        bool isActive(drumID_t drum);

        /*! Returns the active drums' \ref drumID_t for the current step.
        \return a vector containing the \ref drumID_t of the active drums. */
        std::vector<drumID_t> getActive();

        /*! Returns a series of switches for the specified drum's presence in
        each sequence step.
        \param drumID \ref drumID_t of the drum to check.
        \return a vector of `bool`s, `true` if the drum is active in that index'
        step. */
        std::vector<bool> getSteps(drumID_t drumID);

        /*! Returns the entire \ref Sequencer pattern.
        \return a 2D vector of the \ref Sequencer pattern, indexed as [step][drum]. */
        std::vector<std::vector<bool>> getSequence();

        /*! Get the current step number.
        \return the current step number. */
        int getStepNum();

        /*! Clear the \ref Sequencer pattern. */
        void clear();

        /*! Resets the \ref Sequencer to initial conditions.
        \param clearSteps whether to clear the \ref Sequencer pattern. */
        void reset(bool clearSteps = true);

        /*! Adds the specified drum to the specified step.
        \param drum \ref drumID_t of the drum to add.
        \param step ID of the step to be modified. */
        void add(drumID_t drum, int step);

        /*! Adds the specified drum to the current step.
        \param drum \ref drumID_t of the drum to add. */
        void add(drumID_t drum);

        /*! Removes the specified drum from the specified step.
        \param drum \ref drumID_t of the drum to remove.
        \param step ID of the step to be modified. */
        void remove(drumID_t drum, int step);

        /*! Removes the specified drum from the current step.
        \param drum \ref drumID_t of the drum to remove. */
        void remove(drumID_t drum);

        /*! Toggles the specified drum in the specified step.
        \param drum \ref drumID_t of the drum to toggle.
        \param step ID of the step to be modified. */
        void toggle(drumID_t drum, int step);

        /*! Toggles the specified drum in the current step.
        \param drum \ref drumID_t of the drum to toggle. */
        void toggle(drumID_t drum);
    
    private:
        /*! Container for \ref _SequenceStep objects. */
        std::vector<_SequenceStep> steps;
        /*! Number of steps in the sequence. */
        int numSteps;

        /*! Sets the number of steps.
        Unstable for active use.
        \param n desired number of sequence steps. */
        void setNumSteps(int n);

        /*! Index of the current step, e.g. in the \ref steps vector. */
        int stepNum;
        /*! Call to update the active step ID. */
        void _updateStepID();

        /*! Pointer to currently active \ref _SequenceStep object. */
        _SequenceStep* currentStep;
        /*! Call to update the active step pointer.
        Should be called after the active step ID is updated
        (see \ref _updateStepID). */
        void _updateStepPtr();
};


/*! \ref Metronome derived class to clock a \ref Sequencer. */
class SequencerClock : public clock::Metronome {
    public:
        /*! Constructor.
        Sets the \ref Sequencer to be clocked.
        \param s \ref Sequencer object to be clocked.
        \param p \ref audio::PlaybackEngine object for triggering the active drums. */
        SequencerClock(std::shared_ptr<Sequencer> s, audio::PlaybackEngine& p);

        /*! Override the tick method.
        Clocks the \ref Sequencer given to the constructor. */
        void tick() override;
    
    private:
        /*! Pointer to the \ref Sequencer object to be clocked. */
        std::shared_ptr<Sequencer> seq = nullptr;

        /*! Pointer to the \ref audio::PlaybackEngine used for triggering the active
        drums. */
        audio::PlaybackEngine* pbe;
};

} // namespace drumpi

#endif // define SEQUENCER_H