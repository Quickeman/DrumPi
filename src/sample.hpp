// File: sample.hpp
#ifndef DRUMPI_SAMPLE_H
#define DRUMPI_SAMPLE_H

#include <string>
#include <vector>

namespace drumpi {
namespace audio {

/*! Handler class for drum samples. */
class Sample {
    public:
        /*! Class constructor.
        \param filepath the file path of an audio file, e.g. "~/DrumPi/samples/kick.wav"
        \param bufferSize the audio output buffer size, in samples. */
        Sample(std::string filepath, const int bufferSize);

        /*! Returns a buffer's worth of samples.
        \return a buffer of samples. */
        std::vector<int> getSamples();

        /*! Returns the number of buffers remaining in sample.
        \return the number of buffers of playback remaining. */
        int getPlayhead();

        /*! Returns `true` if the sample is currently being played back. */
        bool isActive();

        /*! Halts playback and returns playhead to start of sample. */
        void reset();
    private:
        /*! Retrieve the audio from the given file. */
        void getSamplesFromFile(std::string filepath);
        /*! The audio sample, stored in a 2D vector to pre-seperate into buffers. */
        std::vector<std::vector<int>> sample;
        /*! Number of buffers in the audio sample. */
        int numBuffers;
        /*! The number of buffers of playback elapsed. */
        int playhead;
};

} // namespace audio
} // namespace drumpi

#endif // define DRUMPI_SAMPLE_H