#include "audioLibrary.hpp"

using namespace drumpi;
using namespace audio;

AudioLibrary::AudioLibrary() {
    audioDir = "audio/";

    bankDirPre = "bank";

    drumNamePre = "drum";

    extensions[SOURCE_GENERALISED] = "";
    extensions[SOURCE_PREGENERATED] = ".wav";
}

std::string AudioLibrary::getFilepath(drumID_t drum, int bank, sampleSourceType_t type) {
    return
        DRUMPI_DIR // DrumPi root directory
        + audioDir // Audio directory
        + bankDirPre + std::to_string(bank) + "/" // Bank directory
        + drumNamePre + std::to_string(drum + 1) // File name
        + extensions[type] // File extension
    ;
}