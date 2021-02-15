# Specify the minimum version of CMake that can run this script
cmake_minimum_required(VERSION 3.12)

# Project name and version
project(DrumPi VERSION 1.0)

# Request C++ 11 standard features
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(test)

# Enable testing
enable_testing()

# Add tests
add_test(NAME DrumPiTest COMMAND Test)