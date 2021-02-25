// File: sampleSource.hpp
#ifndef DRUMPI_SAMPLE_H
#define DRUMPI_SAMPLE_H

#include <string>
#include <vector>

// #include <wave/file.h>

#include "defs.hpp"

namespace drumpi {
namespace audio {

/*! Abstract class for sample retieval.
\param T data format of playback samples. */
class SampleSource {
    public:
        /*! Constructor. */
        SampleSource();

        /*! Returns a buffer of samples.
        \param nSamples number of samples to be returned.
        \return sample buffer of length `nSamples`. */
        virtual std::vector<sample_t> getSamples(int nSamples) = 0;// {std::vector<T> v; return v;}

        /*! Resets the source to initial conditions. */
        virtual void reset() = 0;// {}

        /*! Returns the status of the source.
        Sets status to `READY` if currently `FINISHED`.
        \return status code of source. */
        virtual sampleSourceStatus_t getStatus() = 0;// {return SOURCE_ERROR;}

        /*! Returns the type of source represented by the object.
        \return type code of source */
        sampleSourceType_t getType();

    protected:
        /*! Status of the source. */
        sampleSourceStatus_t status;
        /*! Type of source. */
        sampleSourceType_t type;
};

/*! Handler class for drum samples. */
class AudioClip : public SampleSource {
    public:
        /*! Default constructor. */
        AudioClip();

        /*! Class constructor.
        \param filepath the file path of an audio file, e.g. "~/DrumPi/samples/kick.wav". */
        AudioClip(std::string filepath);

        /*! Returns a buffer of samples.
        \param nSamples number of samples to be returned.
        \return sample buffer of length `nSamples`. */
        std::vector<sample_t> getSamples(int nSamples) override;

        /*! Halts playback and returns playhead to start of clip. */
        void reset() override;

        /*! Returns the status of the audio clip's playback.
        Sets status to `READY` if currently `FINISHED`.
        \return status code of clip. */
        sampleSourceStatus_t getStatus() override;

        /*! Like `reset()`, but completely re-loads the clip.
        Not recommended for real-time use, only call to recover from errors. */
        void hardReset();

    private:
        /*! Retrieve the audio from the given file. */
        void loadFile();
        /*! File path of the audio clip to load. */
        std::string filepath;
        /*! Container for the audio clip. */
        std::vector<sample_t> clip;

        /*! Number of samples in the audio clip. */
        int numSamples;
        /*! The number of samples of playback elapsed. */
        int playhead;

        /*! Calculates the number of samples remaining for playback. */
        int samplesRemaining();
};

} // namespace audio
} // namespace drumpi

#endif // define DRUMPI_SAMPLE_H