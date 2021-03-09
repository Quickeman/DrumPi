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
	BOOST_CHECK(app.currentstate->label == "performancemode");
}

BOOST_AUTO_TEST_CASE(changing_state) {
	Application app;
	app.setState(1);

	BOOST_CHECK(app.currentstate->label == "sequencermode");
}
