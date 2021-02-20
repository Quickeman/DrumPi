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
    int r = 500; // rate = 500ms

    c.setRate(r);
    
    BOOST_CHECK_EQUAL(r, c.getRate());
}

BOOST_AUTO_TEST_CASE(counter) {
    // Test the clocking with a basic ticker counter
    class TestClock : public Clock {
        public:
        int i = 0;
        void tick() override {
            i++;
        }
    };
    TestClock c;
    int r = 100; // rate = 100ms
    c.setRate(100);

    BOOST_CHECK_EQUAL(0, c.i);

    c.start();

    BOOST_CHECK_EQUAL(1, c.i);

    std::this_thread::sleep_for(std::chrono::milliseconds(110));

    BOOST_CHECK_EQUAL(2, c.i);

    std::this_thread::sleep_for(std::chrono::milliseconds(110));

    BOOST_CHECK_EQUAL(3, c.i);
}

BOOST_AUTO_TEST_CASE(stopping) {
    // Test the clock stops when requested
    class TestClock : public Clock {
        public:
        int i = 0;
        void tick() override {
            i++;
        }
    };
    TestClock c;
    int r = 10; // rate = 100ms
    c.setRate(r);
    c.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(25));

    int val = c.i;
    c.stop();

    std::this_thread::sleep_for(std::chrono::milliseconds(25));

    BOOST_CHECK_EQUAL(val, c.i);
}