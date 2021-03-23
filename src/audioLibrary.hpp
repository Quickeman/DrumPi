#ifndef DRUMPI_AUDIO_LIBRARY_H
#define DRUMPI_AUDIO_LIBRARY_H

#include <string>
#include <array>

#include "defs.hpp"

namespace drumpi {
namespace audio {

/*! Class for storing and retrieving filepaths of audio sources. */
class AudioLibrary {
    public:
        /*! Constructor.
        Initialises members to correct values. */
        AudioLibrary() {
            audioDir = "audio/";

            filenames = {
                "kick_drum",
                "snare_drum",
                "hand_clap",
                "hi_hat_closed",
                "hit_hat_open",
                "tom_1",
                "tom_2",
                "cymbal"
            };

            extensions = {
                "",
                ".wav"
            };
        }

        /*! Returns the absolute filepath for the given drum and type.
        \param drum ID of the drum to inspect the filepath of.
        \param type type of source to inspect the filepath of.
        \return absolute filepath of the drum's relevant file. */
        std::string getFilepath(drumID_t drum, sampleSourceType_t type) {
            std::string fp;
            fp = DRUMPI_DIR;
            fp.append(audioDir);
            fp.append(filenames[drum]);
            fp.append(extensions[type]);
            return fp;
        }
    
    private:
        /*! Audio files directory (relative). */
        std::string audioDir;
        /*! Extensionless filenames of audio sources. */
        std::array<std::string, NUM_DRUMS> filenames;
        /*! Extensions for the types of audio sources. */
        std::array<std::string, NUM_SOURCE_TYPES> extensions;
};

} // namespace audio
} // namespace drumpi

#endif