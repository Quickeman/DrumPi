#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE AudioEngineTest
#include <boost/test/unit_test.hpp>
#include "audio.hpp"

#include <vector>
#include <thread>

using namespace drumpi;
using namespace audio;
using namespace engine;

class TestCallback : public AudioCallback {
    public:
        std::vector<sample_t> getSamples(int nSamples) override {
            std::vector<sample_t> v;
            v.resize(nSamples);
            for(int i = 0; i < nSamples; i++) {
            phase += 0.01f;
            if (phase >= 1.f) phase -= 1.f;
            v[i] = sinf(2.f * M_PI * phase);
            }
            return v;
        }
    
    private:
	    float phase = 0.f;
};

BOOST_AUTO_TEST_CASE(audioTest) {
    AudioEngine e;
    TestCallback c;
    int err;
    
    BOOST_CHECK(&e);
    BOOST_CHECK(&c);
    
    err = e.setup(c, "DrumPiClient_test");
    BOOST_CHECK(!err);
    
    err = e.start();
    BOOST_CHECK(!err);
    
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    err = e.stop();
    BOOST_CHECK(!err);
}
