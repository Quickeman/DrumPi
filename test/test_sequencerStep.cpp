#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SequencerStepTest
#include <boost/test/unit_test.hpp>
#include <sequencer.hpp>

#include "defs.hpp"

using namespace drumpi;
using namespace sequencer;

BOOST_AUTO_TEST_CASE(constructors) {
    // Test for NULL object pointers
    Step s1;
    Step s2;

    BOOST_CHECK(&s1);
    BOOST_CHECK(&s2);
}

BOOST_AUTO_TEST_CASE(addDrums) {
    // Test adding drums, retrieving individuals and pattern
    Step s;

    std::vector<bool> drums;
    drums.resize(NUM_DRUMS);

    for (int i = 0; i < drums.size(); i++) {
        drums[i] = static_cast<bool>(rand() % 2);
        if (drums[i]) s.addToStep((drumID_t)i);
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
    Step s;
    drumID_t d1 = KICK_DRUM;
    drumID_t d2 = SNARE_DRUM;

    s.addToStep(d1);
    s.addToStep(d2);

    BOOST_CHECK(s.numActive() == 2);

    s.removeFromStep(d2);

    BOOST_CHECK(s.numActive() == 1);
    BOOST_CHECK(s.isActive(d1));
    BOOST_CHECK(!s.isActive(d2));

    s.clear();

    BOOST_CHECK(s.numActive() == 0);
}