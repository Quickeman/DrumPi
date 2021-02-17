add_executable(DrumPi main.cpp)

# Set the output directory for executables
set_target_properties(DrumPi PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Add libraries
add_library(Sequencer sequencer.cpp sequencer.hpp)

# Link libraries to source
target_link_libraries(DrumPi Sequencer)

set_target_properties(Sequencer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)