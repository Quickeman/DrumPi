#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PlaybackEngineTest
#include <boost/test/unit_test.hpp>
#include "playback.hpp"

using namespace drumpi;
using namespace audio;

BOOST_AUTO_TEST_CASE(constructors) {
    // Test for NULL objects
    PlaybackEngine p1;
    PlaybackEngine p2;

    BOOST_CHECK(&p1);
    BOOST_CHECK(&p2);
}

BOOST_AUTO_TEST_CASE(volumes) {
    // Test the volume setters and getters
    PlaybackEngine p;
    float v1 = 1.0;
    drumID_t d1 = KICK_DRUM;
    float v2 = 0.67;
    drumID_t d2 = SNARE_DRUM;
    float vM = 0.5;

    p.setVolume(v1, d1);
    p.setVolume(v2, d2);
    p.setVolume(vM);

    BOOST_CHECK(p.getVolume(d1) == v1);
    BOOST_CHECK(p.getVolume(d2) == v2);
    BOOST_CHECK(p.getVolume() == vM);
}

BOOST_AUTO_TEST_CASE(getsBuffer) {
    // Test the sample getting method returns a non-empty right-sized vector
    PlaybackEngine p;
    int n = 64;

    std::vector<sample_t> v = p.getSamples(n);

    BOOST_CHECK(!v.empty());
    BOOST_CHECK(v.size() == n);
}

BOOST_AUTO_TEST_CASE(triggerSource) {
    // Tests a source can be triggered, the returning of the active sources
    // and untriggering an active source
    PlaybackEngine p;
    int n = 64;
    drumID_t d = KICK_DRUM;
    std::vector<drumID_t> a;
    for (int i = 0; i < NUM_DRUMS; i++) {
        p.setSource((drumID_t)i, SOURCE_PREGENERATED, "~/DrumPi/test/whitenoise.wav");
    }

    p.trigger(d);
    a = p.getActive();

    BOOST_CHECK(!a.empty());
    BOOST_CHECK(a.size() == 1);
    BOOST_CHECK(a[0] == d);

    p.untrigger(d);

    a = p.getActive();
    BOOST_CHECK(a.empty());
}
/**/