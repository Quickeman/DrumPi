#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE AudioEngineTest
#include <boost/test/unit_test.hpp>
#include "audio.hpp"

#include <vector>
#include <thread>

using namespace drumpi;
using namespace audio;

class TestCallback : public AudioCallback {
    public:
        std::vector<sample_t> getSamples(int nSamples) override {
            v.clear();
            v.resize(nSamples);

            for(int i = 0; i < nSamples; i++) {
                phase += 0.01f;

                if (phase > 1.f) phase -= 1.f;

                v[i] = 0.25f * sinf(2.f * M_PI * phase);
            }

            count++;

            return v;
        }

        std::vector<sample_t> v;

        int count = 0;
    
    private:
	    float phase = 0.f;
};

BOOST_AUTO_TEST_CASE(audioTest) {
    JackClient e("DrumPiClient_test");
    TestCallback c;
    int err;
    
    BOOST_CHECK(&e);
    BOOST_CHECK(&c);
    
    err = e.start(c);
    BOOST_CHECK(!err);
    
    std::this_thread::sleep_for(std::chrono::seconds(1));

    BOOST_CHECK(c.count != 0);

    std::vector<sample_t> v = c.v;
    sample_t x = 0.f;
    for (int i = 0; i < 5; i++) {
        x += v[i];
    }
    BOOST_CHECK(x != 0.f);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    err = e.stop();
    BOOST_CHECK(!err);
}
