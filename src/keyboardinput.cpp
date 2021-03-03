//keyboardinput.cpp
//Implementation of keyboard input class
//that detects keyboard presses

#include "keyboardinput.hpp"

using namespace drumpi;
using namespace keyboard;

KeyboardInput::KeyboardInput() {
	const char *input_file = "/dev/input/event0";
	fd = open(input_file, O_RDONLY);
	running = 0;
	testFlag = 0;
	keyPressCount = 0;
	fdset[0].fd = fd;
	fdset[0].events = POLLIN;
}

void KeyboardInput::pollInput() {
	running = 1;
	testFlag = 0;
	keyPressCount = 0;
	while (running) {
		testFlag = 1; 	//flag is only set to 1 if while loop starts

		//poll() checks if an input event has occured
		if (poll(fdset, 1, 0) == 1) {
			read(fd, &ev, sizeof ev);
			if (ev.type == EV_KEY && ev.value == 1) {
				//printf("\n%d key pressed\n", ev.code);
				keyPressCount++;
			}
		}
	}
}

int KeyboardInput::getFileDescriptor() {
   	return fd;
}

int KeyboardInput::getTestFlag() {
   	return testFlag;
}

int KeyboardInput::getKeyPressCount() {
   	return keyPressCount;
}
