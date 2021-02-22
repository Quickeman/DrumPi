//test_keyboard.cpp

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE KeyboardInputTest
#include <boost/test/unit_test.hpp>
#include <keyboard.hpp>

using namespace drumpi;
using namespace kbdinput;

//Check the keyboard input file can be successfully opened
BOOST_AUTO_TEST_CASE(Open_Input_File) {
	KeyboardInput kbd;

	BOOST_CHECK(kbd.fd >= 0);
}
