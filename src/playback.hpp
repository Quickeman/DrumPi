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
Manages audio clips for sending to output.
An instance of this class is used as the callback class for the \ref JackClient. */
class PlaybackEngine : public AudioCallback {
    public:
        /*! Constructor. */
        PlaybackEngine();

        /*! Retrieves samples.
        \param nSamples number of samples to return.
        \return a buffer of samples. */
        std::vector<sample_t> getSamples(int nSamples) override;

        /*! Adds the specified drum to the output stream.
        \param drum \ref drumID_t of the drum to add. */
        void trigger(drumID_t drum);

        /*! Removes the specified drum sample from the output.
        \param drum \ref drumID_t of the drum to remove. */
        void untrigger(drumID_t drum);

        /*! Returns a vector containing the \ref drumID_t of the currently
        active sources.
        \return vector of \ref drumID_t of the currently active sources. */
        std::vector<drumID_t> getActive();

        /*! Increments the playback volume for the passed drum.
        \param drumID \ref drumID_t of the drum to be affected. */
        void volumeUp(drumID_t drum);

        /*! Increments the master output volume. */
        void volumeUp();

        /*! Decrements the playback volume for the passed drum.
        \param drumID \ref drumID_t of the drum to be affected. */
        void volumeDown(drumID_t drum);

        /*! Decrements the master output volume. */
        void volumeDown();

        /*! Returns the current volume of the passed drum.
        \param drum \ref drumID_t of the drum to query.
        \return current volume multiplier of \ref drum. */
        float getVolume(drumID_t drum);

        /*! Returns the current master volume.
        \return current master volume multiplier. */
        float getVolume();

        /*! Loads a bank of drums of a homogenous \ref sampleSourceType_t.
        \param bank ID of the bank of drums to load from.
        \param type \ref sampleSourceType_t of sources to load. */
        sampleSourceStatus_t loadBank(int bank, sampleSourceType_t type);

        /*! Sets the source for the specified drum.
        \param drum \ref drumID_t of the drum to set the type for.
        \param bank ID of the bank of drums to load from.
        \param type \ref sampleSourceType_t of source to load. */
        sampleSourceStatus_t setSource(drumID_t drum, int bank, sampleSourceType_t type);

        /*! Returns the source \ref sampleSourceStatus_t of the given drum.
        \return source status. */
        sampleSourceStatus_t getSourceStatus(drumID_t drum);

        /*! Returns the source \ref sampleSourceType_t for the given drum. 
        \return source type. */
        sampleSourceType_t getSourceType(drumID_t drum);
    
    private:
        /*! Library manager for the audio sources. */
        AudioLibrary library;

        /*! Buffer of samples to allow rapid transfer to Jack. */
        std::vector<sample_t> buffer;

        /*! \ref SampleSource object pointers. */
        std::array<std::unique_ptr<SampleSource>, NUM_DRUMS> sources;
        /*! Switches to store whether each source is being played. */
        std::array<bool, NUM_DRUMS> isTriggered;

        /*! Current master volume multiplier. */
        float masterVol;
        /*! Default master volume multiplier. */
        static constexpr float masterVolDef = 0.75f;
        /*! Current drum volume multipliers. */
        std::array<float, NUM_DRUMS> volumes;
        /*! Default drum volume multiplier. */
        static constexpr float volumeDef = 0.75f;

        /*! Step size for volume increments and decrements. */
        const float volumeStep = 0.05f;
};

} // namespace audio
} // namespace drumpi

#endif // define DRUMPI_PLAYBACK_H