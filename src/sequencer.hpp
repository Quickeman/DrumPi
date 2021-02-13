// File: sequencer.hpp

#ifndef sequencer_h
#define sequencer_h

#define NUM_DRUMS

class SequenceStep {
    public:
        /** Step constructor
         */
        SequenceStep();

        /** Adds the sample with the passed ID to the step
         */
        void addToStep(int id);

        /** Removes the sample with the passed ID from the step
         */
        void removeFromStep(int id);

        /** Returns true if the sample with the passed ID is active in the step
         */
        bool isActive(int id);

        /** Returns the number of active samples in step
         */
        int numActive();
    
    private:
        bool switches[NUM_DRUMS];
};

template<int NUM_STEPS>
class Sequencer {
    public:
        /** Sequencer constructor.
         */
        Sequencer();
        /** Sequencer destructor.
         */
        ~Sequencer();

        /** Returns the current step number.
         */
        int currentStep();
    
    private:
        /** Ticker function.
        Called to update the Sequencer's step tracker
        */
        void tick();

        SequenceStep steps[NUM_STEPS];
};

class Sequencer8Step : Sequencer<8> {};

class Sequencer16Step : Sequencer<16> {};

#endif // define sequencer_h