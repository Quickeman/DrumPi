//keyboardinput.cpp
//Implementation of keyboard input class
//that detects keyboard presses

#include "keyboardinput.hpp"

using namespace drumpi;
using namespace keyboard;

KeyboardInput::KeyboardInput() {
	const char *input_file = "/dev/input/event0";
	fd = open(input_file, O_RDONLY);
	running = 1;
}

void KeyboardInput::pollInput() {
	while (running) {
		n = read(fd, &ev, sizeof ev);
		if (ev.type == EV_KEY && ev.value == 1) {
			printf("\n%d key pressed\n", ev.code);
		}
	}
}
