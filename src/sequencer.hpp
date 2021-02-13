// File: sequencer.hpp

#ifndef sequencer_h
#define sequencer_h

template<int NUM_STEPS>
class Sequencer {
    public:
        Sequencer();
        ~Sequencer();
};

class Sequencer8Step : Sequencer<8> {};

class Sequencer16Step : Sequencer<16> {};

#endif // define sequencer_h