//keyboard.cpp
//Implementation of keyboard input class
//that detects keyboard presses

#include "keyboard.hpp"

void KeyboardInput::poll_input() {
	while (1) {
		n = read(fd, &ev, sizeof ev);
		if (ev.type == EV_KEY && ev.value == 1) {
			printf("\n%d key pressed\n", ev.code);
		}
	}
}