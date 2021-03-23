#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SequencerClockTest
#include <boost/test/unit_test.hpp>
#include "sequencerClock.hpp"
#include <thread>

using namespace drumpi;

BOOST_AUTO_TEST_CASE(constructor) {
    SequencerClock c1;
    SequencerClock c2;

    // Even though they're not linked here, this needs to exist for some reason
    Sequencer s(8);

    BOOST_CHECK(&c1);
    BOOST_CHECK(&c2);
}

BOOST_AUTO_TEST_CASE(clocking) {
    Sequencer s(8);
    SequencerClock c;
    int r = 50;

    BOOST_CHECK(s.getStepNum() == 0);

    c.setSequencer(s);
    c.setRate(r);
    c.start();

    BOOST_CHECK(s.getStepNum() == 1);

    std::this_thread::sleep_for(std::chrono::milliseconds(r + (r / 2)));

    BOOST_CHECK(s.getStepNum() == 2);
}
