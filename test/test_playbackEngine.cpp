#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PlaybackEngineTest
#include <boost/test/unit_test.hpp>
#include "playback.hpp"

using namespace drumpi;
using namespace audio;
using namespace engine;

BOOST_AUTO_TEST_CASE(constructors) {
    // Test for NULL objects
    PlaybackEngine p1;
    PlaybackEngine p2;

    BOOST_CHECK(&p1);
    BOOST_CHECK(&p2);
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
    // and the automatic removal of the source after it's done
    PlaybackEngine p;
    int n = 2056;
    drumID_t d = KICK_DRUM;
    std::vector<drumID_t> a;
    std::vector<sample_t> b;

    p.trigger(d);
    a = p.getActive();

    BOOST_CHECK(!a.empty());
    BOOST_CHECK(a.size() == 1);
    BOOST_CHECK(a[0] == d);

    for (int i = 0; i < 200; i++) {
        b = p.getSamples(n);
    }

    a = p.getActive();
    BOOST_CHECK(a.empty());
}
