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
typedef jack_default_audio_sample_t sample_t;

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

namespace engine {

/*! Error codes for the audio engine system. */
typedef enum _AudioError {
    NO_ERROR = 0,
    CLIENT_OPEN_FAILED,
    CLIENT_ACTIVATE_FAILED,
    SERVER_CONNECT_FAILED,
    NO_PORTS_AVAILABLE,
    NO_PHYSICAL_PORTS,
    PORT_CONNECT_FAILED,
    CLIENT_CLOSE_ERROR
} audioError_t;

} // namespace engine
} // namespace audio
} // namespace drumpi

#endif