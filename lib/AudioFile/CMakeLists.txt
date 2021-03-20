cmake_minimum_required (VERSION 3.12)

add_library (audiofile AudioFile.h)

set_target_properties(audiofile PROPERTIES PUBLIC_HEADER AudioFile.h)