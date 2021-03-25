//test_keyboardthread.cpp

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE KeyboardThreadTest
#include <boost/test/unit_test.hpp>
#include <keyboardthread.hpp>
#include <unistd.h>
#include <stdio.h>

using namespace drumpi;

//Check the keyboard thread can be started and stopped successfully
BOOST_AUTO_TEST_CASE(Start_and_Stop_Kbd_Thread) {

	KeyboardThread kbdThread;
	kbdThread.start();

	/* sleep(2) ensures kbd thread has started
	   and is running kbdIn.pollInput() before stop-thread is called.
	   This checks kbdIn correctly exits pollInput() loop when
	   stop-thread is called */
	sleep(2);

	kbdThread.stop();

	//counts no. of key presses whilst thread was running
	//int count = kbdThread.kbdIn.getKeyPressCount();

	//returns 1 if kbdIn.pollInput()'s while loop started
	//i.e. if thread was started successfully
	int tf = kbdThread.kbdIn.getTestFlag();

	//returns 0 if thread stopped successfully
	int r = kbdThread.kbdIn.running;

	//BOOST_CHECK(count == 1);
	BOOST_CHECK(tf == 1 && r == 0);
}
