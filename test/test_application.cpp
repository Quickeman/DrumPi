//test_application.cpp

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ApplicationTest
#include <boost/test/unit_test.hpp>
#include <application.hpp>

using namespace std;
using namespace drumpi;

BOOST_AUTO_TEST_CASE(constructor) {
	Application app;

	BOOST_CHECK(&app);

	//check default state is performance mode
	BOOST_CHECK(app.currentstate->label == "performancemode");
}

BOOST_AUTO_TEST_CASE(changing_state) {
	Application app;

	//change state to sequencer mode
	app.setState(1);

	//check current state has changed to sequencer mode
	BOOST_CHECK(app.currentstate->label == "sequencermode");
}

BOOST_AUTO_TEST_CASE(interpreting_key_press) {
	Application app;

	//simulate "m" key being pressed to switch to sequencer mode
	app.currentstate->interpretKeyPress(&app, 50);

	//check current state has changed to sequencer mode
	BOOST_CHECK(app.currentstate->label == "sequencermode");
}
