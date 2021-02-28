//keyboardthread.cpp

#include "keyboardthread.hpp"
#include <stdio.h>

using namespace drumpi;
using namespace keyboard;

void KeyboardThread::run() {
	//printf("Keyboard thread has been started.\n");
	kbdIn.pollInput();
}

int KeyboardThread::stop() {
	kbdIn.running = 0;
	this->join();
	return 0;
}
