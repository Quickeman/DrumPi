# Specify the minimum version of CMake that can run this script
cmake_minimum_required(VERSION 3.12)

# Project name and version
project(DrumPi VERSION 1.0)

# Request C++ 11 standard features
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Compile the passed source files into an executable 
add_executable(DrumPi ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

#add_executable(SPITest ${CMAKE_CURRENT_SOURCE_DIR}/src/spi.cpp)

#target_link_libraries(SPITest bcm2835)

# Set the output directory for executables
set_target_properties(DrumPi PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)


#set_target_properties(SPITest 
#	PROPERTIES 
#	RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
