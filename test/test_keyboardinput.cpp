//test_keyboardinput.cpp

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE KeyboardInputTest
#include <boost/test/unit_test.hpp>
#include <keyboardinput.hpp>
#include <application.hpp>

using namespace drumpi;

//Check the keyboard input file can be successfully opened
BOOST_AUTO_TEST_CASE(Open_Input_File) {
	KeyboardInput kbd;

	BOOST_CHECK(kbd.getFileDescriptor() >= 0);
}

//Check the KeyboardInput class can call the Application interpretKeyPress method
BOOST_AUTO_TEST_CASE(application_callback) {
	Application app;
	app.setup();
	
	BOOST_CHECK(app.mode->label == PERFORMANCE_MODE);
	BOOST_CHECK(app.subMode->label == SET_MASTER_VOLUME_MODE);
	
	app.kbdThread.kbdIn.callback->interpretKeyPress(KEY_V);
	
	BOOST_CHECK(app.mode->label == PERFORMANCE_MODE);
	BOOST_CHECK(app.subMode->label == SET_DRUM_VOLUME_MODE);
}
