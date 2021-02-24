// File: defs.hpp
#ifndef DRUMPI_DEFS_H
#define DRUMPI_DEFS_H

/*! Use this file to define types, constants etc that are needed in the program.
DO NOT instantiate any objects, variables etc here. */

#include <jack/jack.h>

namespace drumpi {

#define NUM_DRUMS 8

namespace audio {

/*! Sample data format used by JACK (`float`). */
typedef jack_default_audio_sample_t SAMPLE_FORMAT;

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

} // namespace audio
} // namespace drumpi

#endif