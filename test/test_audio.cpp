#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE AudioEngineTest
#include <boost/test/unit_test.hpp>
#include "audio.hpp"

#include <vector>
#include <thread>

using namespace drumpi;
using namespace audio;
using namespace engine;

BOOST_AUTO_TEST_CASE(constructors) {
    // Test for NULL object references
    AudioEngine e1;
    AudioEngine e2;

    BOOST_CHECK(&e1);
    BOOST_CHECK(&e2);
}

class TestCallback1 : public AudioCallback {
    std::vector<sample_t> getSamples(int nSamples) override {
        std::vector<sample_t> v(nSamples);
        return v;
    }
};

BOOST_AUTO_TEST_CASE(setup) {
    // Test the JACK setup routine
    AudioEngine e;
    TestCallback1 c;

    // Error codes from setup()
    int err = e.setup(c, "DrumPiClient_test1");
    BOOST_CHECK(!err);

    err = e.start();
    BOOST_CHECK(!err);

    err = e.stop();
    BOOST_CHECK(!err);
}

class TestCallback2 : public AudioCallback {
    public:
    int i = 0;
    std::vector<sample_t> getSamples(int nSamples) override {
        std::vector<sample_t> v;
        v.resize(nSamples);
        i++;
        return v;
    }
};

BOOST_AUTO_TEST_CASE(running) {
    // Test JACK runs
    AudioEngine e;
    TestCallback2 c;

    e.setup(c, "DrumPiClient_test2");
    e.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    BOOST_CHECK(c.i);
    e.stop();
}

class TestCallback3 : public AudioCallback {
    std::vector<sample_t> getSamples(int nSamples) override {
        std::vector<sample_t> v;
        v.resize(nSamples);
        for(int i = 0; i < nSamples; i++) v[i] = 0.2f * float(rand()) / float(RAND_MAX);
        return v;
    }
};

BOOST_AUTO_TEST_CASE(output) {
    // Play whitenoise for one second to physically test output
    AudioEngine e;
    TestCallback3 c;

    e.setup(c, "DrumPiClient_test3");
    e.start();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    e.stop();
}