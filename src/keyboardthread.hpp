//keyboardthread.hpp

#ifndef KEYBOARDTHREAD_H
#define KEYBOARDTHREAD_H

#include "CppThread.h"

/*!
 * Class inheriting from CppThread wrapper class
 * that creates a keyboard monitoring thread.
 */
class KeyboardThread : public CppThread {
public:
	int stop();

private:
	void run();
};

#endif	//KEYBOARDTHREAD_H
