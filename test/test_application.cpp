//test_application.cpp

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ApplicationTest
#include <boost/test/unit_test.hpp>
#include <application.hpp>
#include <linux/input.h>

using namespace std;
using namespace drumpi;

BOOST_AUTO_TEST_CASE(constructor) {
	Application app;

	BOOST_CHECK(&app);

	//check default state is performance mode
	BOOST_CHECK(app.currentstate->label == PERFORMANCE_MODE);

	// Check the state of the JackClient
	BOOST_CHECK(app.audioEngine->isOpen());
	BOOST_CHECK(!app.audioEngine->isRunning());

	// Check the display driver is running
	BOOST_CHECK(&app.display);
}


BOOST_AUTO_TEST_CASE(changing_state) {
	Application app;

	//change state to sequencer mode
	app.setState(SET_DRUM_VOLUME_MODE);

	//check current state has changed to sequencer mode
	BOOST_CHECK(app.currentstate->label == SET_DRUM_VOLUME_MODE);
}


BOOST_AUTO_TEST_CASE(interpreting_key_press) {
	Application app;

	//simulate "m" key being pressed to switch to sequencer mode
	app.interpretKeyPress(KEY_V);

	//check current state has changed to sequencer mode
	BOOST_CHECK(app.currentstate->label == SET_DRUM_VOLUME_MODE);
}

BOOST_AUTO_TEST_CASE(interpreting_drum_key) {
	Application app;

	drumID_t testID;

	// Simulate a key press and store return drum ID
	testID = app.currentstate->interpretDrumKey(KEY_A);
	//Check that the ID is correct
	BOOST_CHECK(testID == DRUM_1);

	// Repeat for each drum key
	testID = app.currentstate->interpretDrumKey(KEY_S);
	BOOST_CHECK(testID == DRUM_2);
	testID = app.currentstate->interpretDrumKey(KEY_D);
	BOOST_CHECK(testID == DRUM_3);
	testID = app.currentstate->interpretDrumKey(KEY_F);
	BOOST_CHECK(testID == DRUM_4);
	testID = app.currentstate->interpretDrumKey(KEY_J);
	BOOST_CHECK(testID == DRUM_5);
	testID = app.currentstate->interpretDrumKey(KEY_K);
	BOOST_CHECK(testID == DRUM_6);
	testID = app.currentstate->interpretDrumKey(KEY_L);
	BOOST_CHECK(testID == DRUM_7);
	testID = app.currentstate->interpretDrumKey(KEY_SEMICOLON);
	BOOST_CHECK(testID == DRUM_8);
}


BOOST_AUTO_TEST_CASE(changing_to_SetTempoMode) {
	Application app;

	//simulate "t" key being pressed to switch to SetTempoMode
	//should do nothing as are in performance mode by default
	app.interpretKeyPress(KEY_T);
	//check current state is still performance mode
	BOOST_CHECK(app.currentstate->label == PERFORMANCE_MODE);

	//switch to sequencer mode
	app.interpretKeyPress(KEY_M);

	//switch to SetTempoMode
	app.interpretKeyPress(KEY_T);
	//check current state is now SetTempoMode
	BOOST_CHECK(app.currentstate->label == SET_TEMPO_MODE);

	//exit SetTempoMode and return to sequencer mode
	app.interpretKeyPress(KEY_T);
	//check state has returned to sequencer mode
	BOOST_CHECK(app.currentstate->label == SEQUENCER_MODE);
}


BOOST_AUTO_TEST_CASE(sequencer_mode_defaults) {
	Application app;

	//check defaults
	BOOST_CHECK(app.sequencermode.currentdrum == DRUM_1);
	BOOST_CHECK(app.sequencermode.currentpage == 0);
}


BOOST_AUTO_TEST_CASE(switching_pages_in_sequencer_mode) {
	Application app;

	//switch to sequencer mode
	app.setState(SEQUENCER_MODE);

	//simulate "tab" key being pressed to change page
	app.interpretKeyPress(KEY_TAB);
	//check current page has switched to page 2
	BOOST_CHECK(app.sequencermode.currentpage == 1);

	//simulate "tab" key being pressed again to change page
	app.interpretKeyPress(KEY_TAB);
	//check current page has switched back to page 1
	BOOST_CHECK(app.sequencermode.currentpage == 0);
}


BOOST_AUTO_TEST_CASE(returning_to_sequencer_mode) {
	Application app;

	//switch to sequencer mode
	app.setState(SEQUENCER_MODE);

	//simulate "tab" key being pressed to change to page 2
	app.interpretKeyPress(KEY_TAB);
	//simulate "s" key being pressed to change active drum to drum S
	app.interpretKeyPress(KEY_S);
	//check current page is still page 2
	BOOST_CHECK(app.sequencermode.currentpage == 1);
	
	// Check active drum is now drum S
	// This test will fail until the getDrumIDFromKey() function is implemented
	// Function name just a placeholder, can be whatever
	//BOOST_CHECK(app.sequencermode.currentdrum == app.currentstate->interpretDrumKey(KEY_S);

	//leave sequencer mode (switch to performance mode)
	app.interpretKeyPress(KEY_M);
	//return to sequencer mode
	app.interpretKeyPress(KEY_M);
	//check sequencer mode variables have returned to defaults
	BOOST_CHECK(app.sequencermode.currentpage == 0);
	BOOST_CHECK(app.sequencermode.currentdrum == DRUM_1);
}


BOOST_AUTO_TEST_CASE(changing_to_SetDrumVolumeMode) {
	Application app;

	//switch to SetDrumVolumeMode from default performance mode
	app.interpretKeyPress(KEY_V);
	//check state has changed to SetDrumVolumeMode
	BOOST_CHECK(app.currentstate->label == SET_DRUM_VOLUME_MODE);

	//exit SetDrumVolumeMode
	app.interpretKeyPress(KEY_V);
	//check state has returned to performance mode
	BOOST_CHECK(app.currentstate->label == PERFORMANCE_MODE);
	
	//switch to sequencer mode
	app.setState(SEQUENCER_MODE);
	
	//switch to SetDrumVolumeMode
	app.interpretKeyPress(KEY_V);
	//check state has changed to SetDrumVolumeMode
	BOOST_CHECK(app.currentstate->label == SET_DRUM_VOLUME_MODE);
	
	//exit SetDrumVolumeMode
	app.interpretKeyPress(KEY_BACKSPACE);
	//check state has this time returned to sequencer mode
	BOOST_CHECK(app.currentstate->label == SEQUENCER_MODE);
}
