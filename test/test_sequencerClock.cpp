#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SequencerClockTest
#include <boost/test/unit_test.hpp>
#include "sequencer.hpp"
#include <thread>
#include <memory>

using namespace drumpi;

BOOST_AUTO_TEST_CASE(constructor) {
    std::shared_ptr<Sequencer> s(new Sequencer(8));
    SequencerClock c1(s);
    SequencerClock c2(s);

    BOOST_CHECK(&c1);
    BOOST_CHECK(&c2);
}

BOOST_AUTO_TEST_CASE(clocking) {
    std::shared_ptr<Sequencer> s(new Sequencer(8));
    SequencerClock c(s);
    int r = 50;

    BOOST_CHECK(s->getStepNum() == 0);

    c.setRate(r);
    c.start();

    BOOST_CHECK(s->getStepNum() == 1);

    std::this_thread::sleep_for(std::chrono::milliseconds(r + (r / 2)));

    BOOST_CHECK(s->getStepNum() == 2);
}
