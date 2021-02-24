# Specify the minimum version of CMake that can run this script
cmake_minimum_required(VERSION 3.12)

# Project name and version
project(DrumPi VERSION 1.0)

# Generate compile_commands.json for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Request C++ 11 standard features
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add subdirectories
add_subdirectory(lib)

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
# file(GLOB HDRS src/*.hpp)
# Run through each source file
foreach(srcName ${SRCS})
    # Get extension-less filename
    get_filename_component(libName ${srcName} NAME_WE)
    # Add library
    add_library(${libName} src/${libName}.cpp)
    # Put libraries in /lib/src
    set_target_properties(${libName} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY lib/src)
    target_link_libraries(${libName} wiringPi)
    #target_link_libraries(libMax7219 wiringPi)
    # Link library to DrumPi
    target_link_libraries(sourceLib ${libName})
endforeach(srcName)


# Link source library to DrumPi
target_link_libraries(DrumPi sourceLib)

### UNIT TESTING ###

# Enable testing
enable_testing()

# Use Boost library for unit tests
find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
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
    target_link_libraries(${testName} ${Boost_LIBRARIES} sourceLib)
    # Put test executables in their own directory
    set_target_properties(${testName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY test/testBin)

    # Find wiringPi library
    target_link_libraries(test_display wiringPi)
    # Add test to execution
    add_test(NAME ${testName}
             WORKING_DIRECTORY test/testBin
             COMMAND ${testName}
            )
endforeach(testSrc)

