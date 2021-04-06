// File: defs.hpp
#ifndef DRUMPI_DEFS_H
#define DRUMPI_DEFS_H

/*! Use this file to define types, constants etc that are needed in the program.
DO NOT instantiate any objects, variables etc here. */

#include <jack/jack.h>

namespace drumpi {

// Stop VSC etc. thinking this hasn't been defined (defined in CMakeLists)
#ifndef PROJECT_ROOT_DIR
#define PROJECT_ROOT_DIR ""
#endif

/*! DrumPi project root directory.
Used for loading audio files where the absolute path is required. */
#define DRUMPI_DIR PROJECT_ROOT_DIR

/*! ID numbers for each of the DrumPi's drums. */
typedef enum _DrumIDs {
    DRUM_1 = 0,
    DRUM_2,
    DRUM_3,
    DRUM_4,
    DRUM_5,
    DRUM_6,
    DRUM_7,
    DRUM_8,

    // Number of drums
    // ALWAYS LEAVE LAST!
    _NUM_DRUMS
} drumID_t;

/*! The number of drums available in the DrumPi. */
#define NUM_DRUMS (int)_DrumIDs::_NUM_DRUMS

typedef enum _StateLabels {
    PERFORMANCE_MODE,
    SEQUENCER_MODE,
    SET_TEMPO_MODE,
    SET_DRUM_VOLUME_MODE
} stateLabel_t;

namespace audio {

/*! Sample data format used by JACK (`float`). */
typedef jack_default_audio_sample_t sample_t;

/*! Defines the type of sample source. */
typedef enum _SampleSourceTypes {
    SOURCE_GENERALISED,
    SOURCE_PREGENERATED,

    // Number of source types
    _NUM_SOURCE_TYPES
} sampleSourceType_t;

#define NUM_SOURCE_TYPES (int)_SampleSourceTypes::_NUM_SOURCE_TYPES

/*! Defines the status of a SampleSource-type object. */
typedef enum _SampleSourceStatus {
    SOURCE_LOADING,
    SOURCE_READY,
    SOURCE_ACTIVE,
    SOURCE_FINISHED,
    SOURCE_ERROR
} sampleSourceStatus_t;

/*! Error codes for the audio engine system. */
typedef enum _AudioError {
    NO_ERROR = 0,
    CLIENT_OPEN_FAILED,
    CLIENT_ACTIVATE_FAILED,
    SERVER_CONNECT_FAILED,
    NO_PORTS_AVAILABLE,
    NO_PHYSICAL_PORTS,
    PORT_CONNECT_FAILED,
    CLIENT_DEACTIVATE_ERROR,
    CLIENT_CLOSE_ERROR
} audioError_t;

} // namespace audio
} // namespace drumpi

#endif
