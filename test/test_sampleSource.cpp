#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SampleSourceTest
#include <boost/test/unit_test.hpp>
#include "sampleSource.hpp"

#include "defs.hpp"

#include <string>

using namespace drumpi;
using namespace audio;

std::string fp = std::string(DRUMPI_DIR).append("test/test_audio_file.wav");

BOOST_AUTO_TEST_CASE(constructors) {
    // Tests for NULL objects
    AudioClip c1(fp);
    AudioClip c2(fp);

    BOOST_CHECK(&c1);
    BOOST_CHECK(&c2);
}

BOOST_AUTO_TEST_CASE(getsType) {
    // Tests the setting and retrieving of the source type
    AudioClip c(fp);

    BOOST_CHECK(c.getType() == SOURCE_PREGENERATED);
}

BOOST_AUTO_TEST_CASE(getsBuffer) {
    // Tests a non-empty buffer is returned
    AudioClip c(fp);
    int n = 64;
    std::vector<sample_t> v;

    v = c.getSamples(n);

    BOOST_CHECK(!v.empty());
    BOOST_CHECK(v.size() == n);
}

BOOST_AUTO_TEST_CASE(getsSamples) {
    // Test the samples returned are non-zero
    AudioClip c(fp);
    // Use a large buffer size to allow for non-instant content in file
    int n = 4096;

    BOOST_CHECK(c.getStatus() == SOURCE_READY);

    std::vector<sample_t> v = c.getSamples(n);

    sample_t max = 0.f;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] > max) {
            max = v[i];
        } else if (-v[i] > max) {
            max = -v[i];
        }
    }

    BOOST_CHECK(max != 0.f);
}

BOOST_AUTO_TEST_CASE(getsStatus) {
    // Tests for correct status codes
    AudioClip c(fp);
    int n = 64;
    std::vector<sample_t> v;

    BOOST_CHECK(c.getStatus() == SOURCE_READY);

    v = c.getSamples(n);

    BOOST_CHECK(c.getStatus() == SOURCE_ACTIVE);

    bool active = true;
    sampleSourceStatus_t status;
    while (active) {
        v = c.getSamples(n);
        status = c.getStatus();
        if (status != SOURCE_ACTIVE) active = false;
    }

    BOOST_CHECK(status == SOURCE_FINISHED);

    c.reset();

    BOOST_CHECK(c.getStatus() == SOURCE_READY);
}

BOOST_AUTO_TEST_CASE(reset) {
    // Tests source resetting
    AudioClip c(fp);
    int n = 64;
    std::vector<sample_t> v;

    v = c.getSamples(n);

    BOOST_CHECK(c.getStatus() == SOURCE_ACTIVE);

    c.reset();

    BOOST_CHECK(c.getStatus() == SOURCE_READY);
}
