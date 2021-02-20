#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MetronomeTest
#include <boost/test/unit_test.hpp>
#include <clock.hpp>
#include <thread>

using namespace drumpi;
using namespace clock;

BOOST_AUTO_TEST_CASE(constructors) {
    // Test for NULL object pointers
    Metronome m1;
    Metronome m2;

    BOOST_CHECK(&m1);
    BOOST_CHECK(&m2);
}

BOOST_AUTO_TEST_CASE(bpmToMsConversion) {
    // Test BPM -> ms conversion
    BOOST_CHECK_EQUAL(500, bpmToMs(120));
    BOOST_CHECK_EQUAL(1000, bpmToMs(60));
}

BOOST_AUTO_TEST_CASE(setRateBpm) {
    // Test rate setting with BPM
    Metronome m;
    int bpm = 90;
    int ms = 750;//bpmToMs(bpm);
    m.setRateBPM(bpm);

    BOOST_CHECK_EQUAL(bpm, m.getRateBPM());
    BOOST_CHECK_EQUAL(ms, m.getRate());
}