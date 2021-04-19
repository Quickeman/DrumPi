#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MetronomeTest
#include <boost/test/unit_test.hpp>
#include <clock.hpp>
#include <thread>

using namespace drumpi;
using namespace clock;

class TestMetronome : public Metronome {
    public:
        void tick() override {}
};

BOOST_AUTO_TEST_CASE(constructors) {
    // Test for NULL object pointers
    TestMetronome m1;
    TestMetronome m2;

    BOOST_CHECK(&m1);
    BOOST_CHECK(&m2);
}

BOOST_AUTO_TEST_CASE(bpmToMsConversion) {
    // Test BPM -> ms conversion
    BOOST_CHECK(bpmToMs(120) == 500);
    BOOST_CHECK(bpmToMs(60) == 1000);
    BOOST_CHECK(bpmToMs(90) == 666);
}

BOOST_AUTO_TEST_CASE(setRateBpm) {
    // Test rate setting with BPM
    TestMetronome m;
    int bpm = 90;
    int ms = bpmToMs(bpm);
    m.setRateBPM(bpm);

    BOOST_CHECK(m.getRateBPM() == bpm);
    BOOST_CHECK(m.getRate() == ms);
}