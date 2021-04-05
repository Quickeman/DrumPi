// File: playback.hpp
#ifndef DRUMPI_PLAYBACK_H
#define DRUMPI_PLAYBACK_H

#include <vector>
#include <memory>
#include <array>

#include "defs.hpp"
#include "audio.hpp"
#include "sampleSource.hpp"
#include "audioLibrary.hpp"

namespace drumpi {
namespace audio {

/*! Sample handling class.
Manages audio clips for sending to output. */
class PlaybackEngine : public AudioCallback {
    public:
        /*! Constructor. */
        PlaybackEngine();

        /*! Retrieves samples.
        \param nSamples number of samples to return.
        \return a buffer of samples. */
        std::vector<sample_t> getSamples(int nSamples) override;

        /*! Adds the specified drum to the output engine.
        \param drum ID of the drum to add. */
        void trigger(drumID_t drum);

        /*! Removes the specified drum sample from the output.
        \param drum ID of the drum to remove. */
        void untrigger(drumID_t drum);

        /*! Returns a vector containing the IDs of the currently active sources.
        \return IDs of the currently active sources. */
        std::vector<drumID_t> getActive();

        /*! Increments the playback volume for the passed drum.
        \param drumID ID of the drum to be affected. */
        void volumeUp(drumID_t drum);

        /*! Increments the master output volume. */
        void volumeUp();

        /*! Decrements the playback volume for the passed drum.
        \param drumID ID of the drum to be affected. */
        void volumeDown(drumID_t drum);

        /*! Decrements the master output volume. */
        void volumeDown();

        /*! Returns the current volume of the passed drum.
        \param drum ID of the drum to look at.
        \return current volume multiplier of `drum`. */
        float getVolume(drumID_t drum);

        /*! Returns the current master volume.
        \return current master volume multiplier. */
        float getVolume();

        /*! Sets the source for the specified drum.
        \param drum ID of the drum to set the type for.
        \param type type of source. */
        sampleSourceStatus_t setSource(drumID_t drum, sampleSourceType_t type);

        /*! Returns the source status of the given drum.
        \return source status. */
        sampleSourceStatus_t getSourceStatus(drumID_t drum);

        /*! Returns the source type for the given drum. 
        \return source type. */
        sampleSourceType_t getSourceType(drumID_t drum);
    
    private:
        /*! Library manager for the audio sources. */
        AudioLibrary library;

        /*! Buffer of samples to allow rapid transfer to JACK. */
        std::vector<sample_t> buffer;

        /*! SampleSource object pointers. */
        std::array<std::unique_ptr<SampleSource>, NUM_DRUMS> sources;
        /*! Switches to store whether each source is being played. */
        std::array<bool, NUM_DRUMS> isTriggered;

        /*! Current master volume multiplier. */
        float masterVol;
        /*! Default master volume multiplier. */
        static constexpr float masterVolDef = 1.f;
        /*! Current drum volume multipliers. */
        std::array<float, NUM_DRUMS> volumes;
        /*! Default drum volume multiplier. */
        static constexpr float volumeDef = 1.f;

        /*! Step size for volume increments and decrements. */
        const float volumeStep = 0.05f;
};

} // namespace audio
} // namespace drumpi

#endif // define DRUMPI_PLAYBACK_H