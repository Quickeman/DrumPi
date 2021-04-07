#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TimerTest
#include <boost/test/unit_test.hpp>
#include <clock.hpp>
#include <thread>

using namespace drumpi;
using namespace clock;

class TestTimer : public Timer {
    public:
    int i = 0;
    void trigger() override {
        i++;
    }
};

BOOST_AUTO_TEST_CASE(constructors) {
    // Test for NULL object pointers
    TestTimer t1;
    TestTimer t2;

    BOOST_CHECK(&t1);
    BOOST_CHECK(&t2);
}

BOOST_AUTO_TEST_CASE(triggerTimeSetting) {
    // Test that Timer delay is set properly
    TestTimer t;
    int d = 100; // delay = 100ms

    t.setTime(d);

    BOOST_CHECK_EQUAL(d, t.getTime());
}

BOOST_AUTO_TEST_CASE(incrementOnce) {
    // Test that the Timer triggers once and only once
    TestTimer t;
    int d = 20; // delay = 20ms
    t.setTime(d);

    BOOST_CHECK_EQUAL(0, t.i);
    BOOST_CHECK(!t.isActive());

    t.start();

    BOOST_CHECK(t.isActive());
    BOOST_CHECK_EQUAL(0, t.i);

    std::this_thread::sleep_for(std::chrono::milliseconds(d + (d/10)));

    BOOST_CHECK_EQUAL(1, t.i);
    BOOST_CHECK(!t.isActive());

    std::this_thread::sleep_for(std::chrono::milliseconds(d * 2));

    BOOST_CHECK_EQUAL(1, t.i);
}

BOOST_AUTO_TEST_CASE(stopTimer) {
    // Test stopping the timer before the timer triggers
    TestTimer t;
    int d = 20; // delay = 20ms
    t.setTime(d);

    t.start();

    BOOST_CHECK(t.isActive());

    std::this_thread::sleep_for(std::chrono::milliseconds(d/2));

    t.stop();

    BOOST_CHECK(!t.isActive());
    BOOST_CHECK_EQUAL(0, t.i);

    std::this_thread::sleep_for(std::chrono::milliseconds(d));

    BOOST_CHECK_EQUAL(0, t.i);
}