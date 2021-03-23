#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE AudioLibraryTest
#include <boost/test/unit_test.hpp>
#include "audioLibrary.hpp"
#include "AudioFile.h"
#include "defs.hpp"

using namespace drumpi;
using namespace audio;

BOOST_AUTO_TEST_CASE(loadingWavFiles) {
    AudioLibrary lib;
    for (int i = 0; i < NUM_DRUMS; i++) {
        AudioFile<sample_t> f;
        bool loaded;
        loaded = f.load(lib.getFilepath((drumID_t)i, SOURCE_PREGENERATED));
        BOOST_CHECK(loaded);
    }
}