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
    drumID_t d1 = KICK_DRUM;
    drumID_t d2 = SNARE_DRUM;

    p.volumeDown(d1);
    p.volumeUp(d2);
    p.volumeDown();

    BOOST_CHECK(p.getVolume(d1) == 0.95f);
    BOOST_CHECK(p.getVolume(d2) == 1.0f);
    BOOST_CHECK(p.getVolume() == 0.95f);

    int c = 22;
    while (c) {
        p.volumeDown(d2);
        c--;
    }
    BOOST_CHECK(p.getVolume(d2) == 0.0f);
    
    p.volumeUp(d2);
    BOOST_CHECK(p.getVolume(d2) == 0.05f);
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
        p.setSource((drumID_t)i, SOURCE_PREGENERATED);
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
