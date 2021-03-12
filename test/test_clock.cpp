#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ClockTest
#include <boost/test/unit_test.hpp>
#include <clock.hpp>
#include <thread>

using namespace drumpi;
using namespace clock;

BOOST_AUTO_TEST_CASE(constructors) {
    // Test for NULL object pointers
    Clock c1;
    Clock c2;

    BOOST_CHECK(&c1);
    BOOST_CHECK(&c2);
}

BOOST_AUTO_TEST_CASE(rateSetting) {
    // Test the clock rate setting & retrieving
    Clock c;
    int r = 100; // rate = 100ms

    c.setRate(r);
    
    BOOST_CHECK_EQUAL(r, c.getRate());
}

class TestClock1 : public Clock {
    public:
    int i = 0;
    void tick() override {
        i++;
    }
};

BOOST_AUTO_TEST_CASE(counter) {
    // Test the clocking with a basic ticker counter
    TestClock1 c;
    int r = 10; // rate = 10ms
    c.setRate(r);

    BOOST_CHECK_EQUAL(0, c.i);

    c.start();

    BOOST_CHECK_EQUAL(1, c.i);

    std::this_thread::sleep_for(std::chrono::milliseconds(r + (r/10)));

    BOOST_CHECK_EQUAL(2, c.i);

    std::this_thread::sleep_for(std::chrono::milliseconds(r + (r/10)));

    BOOST_CHECK_EQUAL(3, c.i);
}

BOOST_AUTO_TEST_CASE(stopping) {
    // Test the clock stops when requested
    TestClock1 c;
    int r = 10; // rate = 10ms
    c.setRate(r);
    c.start();

    std::this_thread::sleep_for(std::chrono::milliseconds((2*r) + (r / 2)));

    int val = c.i;
    c.stop();

    std::this_thread::sleep_for(std::chrono::milliseconds((2*r) + (r / 2)));

    BOOST_CHECK_EQUAL(val, c.i);
}

BOOST_AUTO_TEST_CASE(activeRateSetting) {
    // Test changing clock rate while Clock is active/ticking
    TestClock1 c;
    int r1 = 40; // rate1 = 40ms
    int r2 = 10; // rate2 = 10ms
    c.setRate(r1);
    c.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(r1 + (r1/2)));

    BOOST_CHECK_EQUAL(2, c.i);

    c.setRate(r2);

    BOOST_CHECK_EQUAL(2, c.i);

    std::this_thread::sleep_for(std::chrono::milliseconds((r1/2) + (r2/2)));

    BOOST_CHECK_EQUAL(3, c.i);

    std::this_thread::sleep_for(std::chrono::milliseconds(r2*3));

    BOOST_CHECK_EQUAL(6, c.i);
}