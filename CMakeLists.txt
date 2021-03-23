# Specify the minimum version of CMake that can run this script
cmake_minimum_required(VERSION 3.12)

# Project name and version
project(DrumPi VERSION 1.0)

# Generate compile_commands.json for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Request C++ 11 standard features
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

### OUTPUT TARGET ###

add_executable(DrumPi src/main.cpp)

# Set the output directory for executables
set_target_properties(DrumPi PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin)


### SOURCE CODE ###

# Library of all source code
add_library(sourceLib src/.dummy.cxx)
set_target_properties(sourceLib PROPERTIES ARCHIVE_OUTPUT_DIRECTORY lib/src)

# Include source and header files
file(GLOB SRCS src/*.cpp)
# Run through each source file
foreach(srcName ${SRCS})
    # Get extension-less filename
    get_filename_component(libName ${srcName} NAME_WE)
    # Add library
    add_library(${libName} src/${libName}.cpp)
    # Put libraries in /lib/src
    set_target_properties(${libName} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY lib/src)
    # Link library to DrumPi
    target_link_libraries(sourceLib ${libName})
endforeach(srcName)



### LIBRARIES ###

# Create base library from dummy file
add_library(library src/.dummy.cxx)
set_target_properties(library PROPERTIES ARCHIVE_OUTPUT_DIRECTORY lib)

## Add, include and link each library subdirectory
# For pre-compiled libraries (e.g. wiringPi) only linking is needed
# Add
add_subdirectory(
    lib/cppTimer
    lib/AudioFile
)

# Include
include_directories(
    lib/cppTimer
    lib/cppThread
    lib/AudioFile
)

find_package (Threads)

# Link
target_link_libraries(library
    cpptimer
    wiringPi
    jack
    ${CMAKE_THREAD_LIBS_INIT}
)

# Link sum library to DrumPi
target_link_libraries(DrumPi library)


# Link source library to DrumPi
target_link_libraries(DrumPi sourceLib)

### UNIT TESTING ###

# Enable testing
enable_testing()

# Use Boost library for unit tests
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

# Link to source directory
include_directories(${Boost_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/src)

# Include test files
file(GLOB TEST_SRCS test/*.cpp)
# Run through each test file
foreach(testSrc ${TEST_SRCS})
    # Get extension-less file name
    get_filename_component(testName ${testSrc} NAME_WE)
    # Add target
    add_executable(${testName} ${testSrc})
    # Link to Boost and deps

    target_link_libraries(${testName} ${Boost_LIBRARIES} wiringPi sourceLib library)
    # Put test executables in their own directory
    set_target_properties(${testName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY test/testBin)

    # Add test to execution
    add_test(NAME ${testName}
             WORKING_DIRECTORY test/testBin
             COMMAND ${testName}
            )
endforeach(testSrc)

# Add definition for the project root directly for file loading
add_definitions(-DPROJECT_ROOT_DIR="${PROJECT_SOURCE_DIR}/")