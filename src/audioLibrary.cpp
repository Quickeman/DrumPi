#include "audioLibrary.hpp"

using namespace drumpi;
using namespace audio;

AudioLibrary::AudioLibrary() {
    audioDir = "audio/";

    filenames[KICK_DRUM] = "kick_drum";
    filenames[SNARE_DRUM] = "snare_drum",
    filenames[CLAP_DRUM] = "hand_clap",
    filenames[HI_HAT_CLOSED] = "hi_hat_closed",
    filenames[HI_HAT_OPEN] = "hi_hat_open",
    filenames[TOM_1_DRUM] = "tom_1",
    filenames[TOM_2_DRUM] = "tom_2",
    filenames[CYMBAL_DRUM] = "cymbal";

    extensions[SOURCE_GENERALISED] = "";
    extensions[SOURCE_PREGENERATED] = ".wav";
}

std::string AudioLibrary::getFilepath(drumID_t drum, sampleSourceType_t type) {
    std::string fp;
    fp = DRUMPI_DIR;
    fp.append(audioDir);
    fp.append(filenames[drum]);
    fp.append(extensions[type]);
    return fp;
}