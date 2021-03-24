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
}


BOOST_AUTO_TEST_CASE(changing_state) {
	Application app;

	//change state to sequencer mode
	app.setState(SEQUENCER_MODE);

	//check current state has changed to sequencer mode
	BOOST_CHECK(app.currentstate->label == SEQUENCER_MODE);
}


BOOST_AUTO_TEST_CASE(interpreting_key_press) {
	Application app;

	//simulate "m" key being pressed to switch to sequencer mode
	app.currentstate->interpretKeyPress(&app, KEY_M);

	//check current state has changed to sequencer mode
	BOOST_CHECK(app.currentstate->label == SEQUENCER_MODE);
}


BOOST_AUTO_TEST_CASE(changing_to_SetTempoMode) {
	Application app;

	//simulate "t" key being pressed to switch to SetTempoMode
	//should do nothing as are in performance mode by default
	app.currentstate->interpretKeyPress(&app, KEY_T);
	//check current state is still performance mode
	BOOST_CHECK(app.currentstate->label == PERFORMANCE_MODE);

	//switch to sequencer mode
	app.currentstate->interpretKeyPress(&app, KEY_M);

	//switch to SetTempoMode
	app.currentstate->interpretKeyPress(&app, KEY_T);
	//check current state is now SetTempoMode
	BOOST_CHECK(app.currentstate->label == SET_TEMPO_MODE);

	//exit SetTempoMode and return to sequencer mode
	app.currentstate->interpretKeyPress(&app, KEY_T);
	//check state has returned to sequencer mode
	BOOST_CHECK(app.currentstate->label == SEQUENCER_MODE);
}


BOOST_AUTO_TEST_CASE(sequencer_mode_defaults) {
	Application app;

	//check defaults
	BOOST_CHECK(app.sequencermode.currentdrum == KICK_DRUM);
	BOOST_CHECK(app.sequencermode.currentpage == 1);
}


BOOST_AUTO_TEST_CASE(switching_pages_in_sequencer_mode) {
	Application app;

	//switch to sequencer mode
	app.setState(SEQUENCER_MODE);

	//simulate "tab" key being pressed to change page
	app.currentstate->interpretKeyPress(&app, KEY_TAB);
	//check current page has switched to page 2
	BOOST_CHECK(app.sequencermode.currentpage == 2);

	//simulate "tab" key being pressed again to change page
	app.currentstate->interpretKeyPress(&app, KEY_TAB);
	//check current page has switched back to page 1
	BOOST_CHECK(app.sequencermode.currentpage == 1);
}


BOOST_AUTO_TEST_CASE(returning_to_sequencer_mode) {
	Application app;

	//switch to sequencer mode
	app.setState(SEQUENCER_MODE);

	//simulate "tab" key being pressed to change to page 2
	app.currentstate->interpretKeyPress(&app, KEY_TAB);
	//simulate "s" key being pressed to change active drum to drum S
	app.currentstate->interpretKeyPress(&app, KEY_S);
	//check current page is still page 2
	BOOST_CHECK(app.sequencermode.currentpage == 2);
	//check active drum is now drum S (currently snare drum)

	// This test will fail until the getDrumIDFromKey() function is implemented
	// Function name just a placeholder, can be whatever
	// BOOST_CHECK(app.sequencermode.currentdrum == getDrumIDFromKey(KEY_S));

	//leave sequencer mode (switch to performance mode)
	app.currentstate->interpretKeyPress(&app, KEY_M);
	//return to sequencer mode
	app.currentstate->interpretKeyPress(&app, KEY_M);
	//check sequencer mode variables have returned to defaults
	BOOST_CHECK(app.sequencermode.currentpage == 1);
	BOOST_CHECK(app.sequencermode.currentdrum == KICK_DRUM);
}


BOOST_AUTO_TEST_CASE(changing_to_SetDrumVolumeMode) {
	Application app;

	//switch to SetDrumVolumeMode from default performance mode
	app.currentstate->interpretKeyPress(&app, KEY_V);
	//check state has changed to SetDrumVolumeMode
	BOOST_CHECK(app.currentstate->label == SET_DRUM_VOLUME_MODE);

	//exit SetDrumVolumeMode
	app.currentstate->interpretKeyPress(&app, KEY_V);
	//check state has returned to performance mode
	BOOST_CHECK(app.currentstate->label == PERFORMANCE_MODE);

	//switch to sequencer mode
	app.setState(SEQUENCER_MODE);
	
	//switch to SetDrumVolumeMode
	app.currentstate->interpretKeyPress(&app, KEY_V);
	//check state has changed to SetDrumVolumeMode
	BOOST_CHECK(app.currentstate->label == SET_DRUM_VOLUME_MODE);

	//exit SetDrumVolumeMode
	app.currentstate->interpretKeyPress(&app, KEY_V);
	//check state has this time returned to sequencer mode
	BOOST_CHECK(app.currentstate->label == SEQUENCER_MODE);
}
