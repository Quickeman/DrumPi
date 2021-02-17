# # Use Boost library for unit tests
# find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
# # Link to source directory
# include_directories(${PROJECT_SOURCE_DIR}/src ${Boost_INCLUDE_DIRS})
# # Boost defs
# add_definitions(-DBOOST_TEST_DYN_LINK)

# # Link used Boost libraries for convenience
# BoostLibs = ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}


# ### List all unit tests

# # Sequencer
# add_executable(SequencerTest test_sequencer.cpp)
# target_link_libraries(SequencerTest Sequencer ${BoostLibs})
# add_test(NAME SeqTest COMMAND SequencerTest)