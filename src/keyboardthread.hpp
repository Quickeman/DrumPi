//keyboardthread.hpp

#ifndef KEYBOARDTHREAD_H
#define KEYBOARDTHREAD_H

#include "CppThread.h"
#include "keyboardinput.hpp"

namespace drumpi {
namespace keyboard {

/*!
 * Class inheriting from CppThread wrapper class
 * that creates a keyboard monitoring thread.
 */
class KeyboardThread : public CppThread {
public:
	/*! Method to close the thread.*/
	int stop();

	/*! Instance of KeyboardInput class */
	KeyboardInput kbdIn;

	/*! Method called when thread is started. */
	void run();
};

}	//namespace keyboard
}	//namespace drumpi

#endif	//KEYBOARDTHREAD_H
