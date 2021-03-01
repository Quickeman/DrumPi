//test_keyboardthread.cpp

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE KeyboardThreadTest
#include <boost/test/unit_test.hpp>
#include <keyboardthread.hpp>
#include <unistd.h>
#include <stdio.h>

using namespace drumpi;
using namespace keyboard;

//Check the keyboard thread can be started and stopped successfully
BOOST_AUTO_TEST_CASE(Start_and_Stop_Kbd_Thread) {

	KeyboardThread kbdThread;
	kbdThread.start();

	/* sleep command ensures kbd thread has started
	   and is running pollInput() before the thread is stopped */
	sleep(2);

	kbdThread.stop();

	//counts no. of key presses whilst thread was running
	//int count = kbdThread.kbdIn.keypresscount;

	//returns 0 if thread stopped successfully
	int r = kbdThread.kbdIn.running;

	//returns 1 if kbdIn.pollInput()'s' while loop started
	//i.e. if thread was started successfully
	int tf = kbdThread.kbdIn.testflag;

	//BOOST_CHECK(count == 3);
	BOOST_CHECK(r == 0 && tf == 1);
}
