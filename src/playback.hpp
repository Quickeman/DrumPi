// File: playback.hpp
#ifndef DRUMPI_PLAYBACK_H
#define DRUMPI_PLAYBACK_H

#include <vector>
#include <memory>

#include "defs.hpp"
#include "audio.hpp"
#include "sampleSource.hpp"

namespace drumpi {
namespace audio {
namespace engine {

/*! Sample handling class.
Manages audio clips for sending to output. */
template<typename T = SAMPLE_FORMAT>
class PlaybackEngine : public AudioCallback<T> {
    public:
        /*! Constructor. */
        PlaybackEngine();

        /*! Retrieves samples.
        \param nSamples number of samples to return.
        \return a buffer of samples. */
        std::vector<T> getSamples(int nSamples) override;

        /*! Adds the specified drum to the output engine.
        \param id ID of the drum to add. */
        void trigger(drumID_t id);

        /*! Returns a vector containing the IDs of the currently active sources.
        \return IDs of the currently active sources. */
        std::vector<drumID_t> getActive();
    
    private:
        /*! Removes the specified drum sample from the output.
        \param id ID of the drum to remove. */
        void untrigger(drumID_t id);

        /*! Buffer of samples to allow rapid transfer to JACK. */
        std::vector<T> buffer;

        /*! SampleSource object pointers. */
        std::vector<std::unique_ptr<SampleSource<T>>> sources;
        /*! Switches to store whether each source is being played. */
        std::vector<bool> isTriggered;
        /*! Types of sample retrievers. */
        std::vector<sampleSourceType_t> types;

        /*! Counter storing the number of active clips. */
        int numActive;
};

} // namespace engine
} // namespace audio
} // namespace drumpi

#endif // define DRUMPI_PLAYBACK_H