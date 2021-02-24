// File: defs.hpp
#ifndef DRUMPI_DEFS_H
#define DRUMPI_DEFS_H

/*! Use this file to define types, constants etc that are needed in the program.
DO NOT instantiate any objects, variables etc here. */

#include <jack/jack.h>

namespace drumpi {

typedef enum _DrumIDs {
    KICK_DRUM = 0,
    SNARE_DRUM,
    _NUM_DRUMS
} drumID_t;

#define NUM_DRUMS (int)_DrumIDs::_NUM_DRUMS

namespace audio {

/*! Sample data format used by JACK (`float`). */
typedef jack_default_audio_sample_t SAMPLE_FORMAT;

/*! Defines the type of sample source. */
typedef enum _SampleSourceType {
    SOURCE_PREGENERATED,
    SOURCE_GENERALISED
} sampleSourceType_t;

/*! Defines the status of a SampleSource-type object. */
typedef enum _SampleSourceStatus {
    SOURCE_LOADING,
    SOURCE_READY,
    SOURCE_ACTIVE,
    SOURCE_FINISHED,
    SOURCE_ERROR
} sampleSourceStatus_t;

} // namespace audio
} // namespace drumpi

#endif