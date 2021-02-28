//keyboardthread.cpp

#include "keyboardthread.hpp"
#include <stdio.h>

void KeyboardThread::run() {
	printf("Keyboard thread has been started.\n");
}

int KeyboardThread::stop() {
	this->join();
	return 0;
}