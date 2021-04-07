#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SequencerStepTest
#include <boost/test/unit_test.hpp>
#include <sequencer.hpp>

#include "defs.hpp"

using namespace drumpi;

BOOST_AUTO_TEST_CASE(constructors) {
    // Test for NULL object pointers
    _SequenceStep s1;
    _SequenceStep s2;

    BOOST_CHECK(&s1);
    BOOST_CHECK(&s2);
}

BOOST_AUTO_TEST_CASE(addDrums) {
    // Test adding drums, retrieving individuals and pattern
    _SequenceStep s;

    std::array<bool, NUM_DRUMS> drums;

    for (int i = 0; i < NUM_DRUMS; i++) {
        drums[i] = static_cast<bool>(rand() % 2);
        if (drums[i]) s.add((drumID_t)i);
    }

    for (int i = 0; i < drums.size(); i++) {
        BOOST_CHECK(drums[i] == s.isActive((drumID_t)i));
    }

    std::vector<drumID_t> active = s.getActive();
    active.resize(active.size() + 1);
    int ind = 0;
    for (int i = 0; i < drums.size(); i++) {
        if (drums[i]) {
            BOOST_CHECK(active[ind] == i);
            ind++;
        } else {
            BOOST_CHECK(active[ind] != i);
        }
    }
}

BOOST_AUTO_TEST_CASE(removeDrums) {
    // Test removing drums and clearing the pattern
    _SequenceStep s;
    drumID_t d1 = DRUM_1;
    drumID_t d2 = DRUM_2;

    s.add(d1);
    s.add(d2);

    BOOST_CHECK(s.numActive() == 2);

    s.remove(d2);

    BOOST_CHECK(s.numActive() == 1);
    BOOST_CHECK(s.isActive(d1));
    BOOST_CHECK(!s.isActive(d2));

    s.clear();

    BOOST_CHECK(s.numActive() == 0);
}