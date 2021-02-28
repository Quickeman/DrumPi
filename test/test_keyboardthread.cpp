//test_keyboardthread.cpp

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE KeyboardThreadTest
#include <boost/test/unit_test.hpp>
#include <keyboardthread.hpp>

//Check the keyboard thread can be started and stopped successfully
BOOST_AUTO_TEST_CASE(Start_and_Stop_Kbd_Thread) {
	KeyboardThread kbdThread;
	kbdThread.start();
	kbdThread.stop();

	//BOOST_CHECK(kbdThread.stop() == 0);
}
