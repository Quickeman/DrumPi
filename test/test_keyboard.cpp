//test_keyboard.cpp

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE KeyboardInputTest
#include <boost/test/unit_test.hpp>
#include <keyboard.hpp>

//I want a class to open the keyboard input file

BOOST_AUTO_TEST_CASE(Open_Input_File) {
	KeyboardInput kbd;

	//check input file has been sucessfully opened
	BOOST_CHECK(kbd.fd >= 0);
}

//I want keyboard presses to trigger a function
