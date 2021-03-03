//test_keyboardinput.cpp

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE KeyboardInputTest
#include <boost/test/unit_test.hpp>
#include <keyboardinput.hpp>

using namespace drumpi;
using namespace keyboard;

//Check the keyboard input file can be successfully opened
BOOST_AUTO_TEST_CASE(Open_Input_File) {
	KeyboardInput kbd;

	BOOST_CHECK(kbd.getFileDescriptor() >= 0);
}
