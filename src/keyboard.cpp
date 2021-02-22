//keyboard.cpp
//Implementation of keyboard input class
//that detects keyboard presses

#include "keyboard.hpp"

using namespace drumpi;
using namespace kbdinput;

KeyboardInput::KeyboardInput() {
	const char *input_file = "/dev/input/event3";
	fd = open(input_file, O_RDONLY);
}

void KeyboardInput::pollInput() {
	while (1) {
		n = read(fd, &ev, sizeof ev);
		if (ev.type == EV_KEY && ev.value == 1) {
			printf("\n%d key pressed\n", ev.code);
		}
	}
}
