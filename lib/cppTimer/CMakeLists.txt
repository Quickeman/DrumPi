cmake_minimum_required(VERSION 2.8.9)
enable_testing()

add_library(cpptimer STATIC CppTimer.cpp)
TARGET_LINK_LIBRARIES(cpptimer rt)

add_subdirectory(test)

set_target_properties(cpptimer PROPERTIES PUBLIC_HEADER CppTimer.h)
set_target_properties(cpptimer PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/cppTimer)