//keyboardthread.hpp

#ifndef KEYBOARDTHREAD_H
#define KEYBOARDTHREAD_H

#include "CppThread.h"
#include "keyboardinput.hpp"

namespace drumpi {

/*!
 * This class inherits from the CppThread wrapper class
 * and creates a keyboard monitoring thread.
 */
class KeyboardThread : public CppThread {
public:
	/*! Closes the thread.*/
	int stop();

	/*! This method is called when the thread is started. */
	void run();

	/*! Instance of \ref KeyboardInput class. */
	KeyboardInput kbdIn;
};

}	//namespace drumpi

#endif	//KEYBOARDTHREAD_H
