#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SequencerClockTest
#include <boost/test/unit_test.hpp>
#include "sequencerClock.hpp"
#include <thread>

using namespace drumpi;

BOOST_AUTO_TEST_CASE(constructor) {
    Sequencer s(8);
    SequencerClock c1(s);
    SequencerClock c2(s);

    BOOST_CHECK(&c1);
    BOOST_CHECK(&c2);
}

BOOST_AUTO_TEST_CASE(clocking) {
    Sequencer s(8);
    SequencerClock c(s);
    int r = 50;

    c.setRate(r);

    BOOST_CHECK(s.getStepNum() == 0);

    c.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(r + (r / 2)));

    BOOST_CHECK(s.getStepNum() == 1);
}