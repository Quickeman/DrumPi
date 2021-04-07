#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SamplePlaybackTest
#include <boost/test/unit_test.hpp>
#include "audio.hpp"
#include "playback.hpp"

#include <thread>

using namespace drumpi;
using namespace audio;

BOOST_AUTO_TEST_CASE(playback) {
    JackClient a("DrumPi_test_samplePlayback");
    PlaybackEngine p;

    for (int i = 0; i < NUM_DRUMS; i++) {
        p.setSource((drumID_t)i, 0, SOURCE_PREGENERATED);
    }

    a.start(p);

    for (int i = 0; i < NUM_DRUMS; i++) {
        // Trigger each drum sound in turn
        p.trigger((drumID_t)i);
        // Pause for 0.5s between each drum
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    a.stop();
}