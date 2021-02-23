// File: sampleSource.hpp
#ifndef DRUMPI_SAMPLE_H
#define DRUMPI_SAMPLE_H

#include <string>
#include <vector>

// #include <wave/file.h>
#include <audio.hpp>

namespace drumpi {
namespace audio {

/*! Defines the type of sample source. */
typedef enum _SampleSourceType {
    PREGENERATED_CLIP,
    GENERALISED
} sampleSourceType_t;

/*! Defines the status of a SampleSource-type object. */
typedef enum _SampleSourceStatus {
    LOADING,
    READY,
    ACTIVE,
    FINISHED,
    ERROR
} sampleSourceStatus_t;

/*! Abstract class for sample retieval.
\param T data format of playback samples. */
template<typename T = SAMPLE_FORMAT>
class SampleSource {
    public:
        /*! Constructor. */
        SampleSource();

        /*! Returns a buffer of samples.
        \param nSamples number of samples to be returned.
        \return sample buffer of length `nSamples`. */
        virtual std::vector<T> getSamples(int nSamples) {};

        /*! Resets the source to initial conditions. */
        virtual void reset() {};

        /*! Returns the status of the source.
        Sets status to `READY` if currently `FINISHED`.
        \return status code of source. */
        virtual sampleSourceStatus_t getStatus() {};

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
template<typename T = SAMPLE_FORMAT>
class AudioClip : public SampleSource<T> {
    public:
        /*! Class constructor.
        \param filepath the file path of an audio file, e.g. "~/DrumPi/samples/kick.wav". */
        AudioClip(std::string filepath);

        /*! Returns a buffer of samples.
        \param nSamples number of samples to be returned.
        \return sample buffer of length `nSamples`. */
        std::vector<T> getSamples(int nSamples) override;

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
        std::vector<T> clip;

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