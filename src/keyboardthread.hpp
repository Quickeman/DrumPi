//keyboardthread.hpp

#ifndef KEYBOARDTHREAD_H
#define KEYBOARDTHREAD_H

#include "CppThread.h"
#include "keyboardinput.hpp"

namespace drumpi {

/*!
 * Class inheriting from CppThread wrapper class
 * that creates a keyboard monitoring thread.
 */
class KeyboardThread : public CppThread {
public:
	/*! Method to close the thread.*/
	int stop();

	/*! Method called when thread is started. */
	void run();

	/*! Instance of KeyboardInput class */
	KeyboardInput kbdIn;
};

}	//namespace drumpi

#endif	//KEYBOARDTHREAD_H
