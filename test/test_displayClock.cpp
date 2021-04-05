#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SequencerClockTest
#include <boost/test/unit_test.hpp>
#include "display.hpp"
#include <thread>
#include <memory>

using namespace drumpi;

BOOST_AUTO_TEST_CASE(constructor) {
    std::shared_ptr<Display> d(new Display);
    DisplayClock c1(d);
    DisplayClock c2(d);

    BOOST_CHECK(&c1);
    BOOST_CHECK(&c2);
}
