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
        AudioLibrary();

        /*! Returns the absolute filepath for the given drum and type.
        \param drum \ref drumID_t of the drum to inspect the filepath of.
        \param bank ID of the bank of drums to load from.
        \param type \ref sampleSourceType_t of source to inspect the filepath of.
        \return absolute filepath of the relevant file. */
        std::string getFilepath(drumID_t drum, int bank, sampleSourceType_t type);
    
    private:
        /*! Name of the audio directory. */
        std::string audioDir;
        /*! Prefix for the bank directory names. */
        std::string bankDirPre;
        /*! Prefix for the files' names. */
        std::string drumNamePre;
        /*! Extensions for the types of audio sources. */
        std::array<std::string, NUM_SOURCE_TYPES> extensions;
};

} // namespace audio
} // namespace drumpi

#endif