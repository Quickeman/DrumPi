//keyboardinput.cpp
//Implementation of keyboard input class
//that detects keyboard presses

#include <string>
#include <iostream>
#include <fstream>
#include "keyboardinput.hpp"

using namespace drumpi;

KeyboardInput::KeyboardInput() {
	std::string kbdConf = std::string(DRUMPI_DIR).append("kbd-config.txt");
	std::string kbdID;
	std::string kbdPath;
	std::ifstream kbdConfigFile;
		
	kbdConfigFile.open (kbdConf, std::ios::in);
	kbdConfigFile >> kbdID;
	
	kbdPath = "/dev/input/by-id/" + kbdID;
	const char* kbdFilePath = kbdPath.c_str();	//conversion necessary since open() expects a const char
	printf("USB Keyboard Path: %s\n", kbdFilePath);
	
	kbdConfigFile.close();
	
	fd = open(kbdFilePath, O_RDONLY);
	running = 0;
	testFlag = 0;
	keyPressCount = 0;
	fdset[0].fd = fd;
	fdset[0].events = POLLIN;
}

void KeyboardInput::pollInput() {
	running = 1;
	testFlag = 0;
	//keyPressCount = 0;
	while (running) {
		testFlag = 1; 	//flag is only set to 1 if while loop starts

		//poll() checks if an input event has occured
		if (poll(fdset, 1, 0) == 1) {
			read(fd, &ev, sizeof ev);
			if (ev.type == EV_KEY && ev.value == 1) {
				if (ev.code == KEY_ESC) {
					tcflush(STDIN_FILENO, TCIFLUSH);
					callback->running = false;
				}
				//printf("\n%d key pressed\n", ev.code);
				callback->interpretKeyPress(ev.code);
				//keyPressCount++;
			}
		}
	}
}

void KeyboardInput::connectCallback(ApplicationCallback* app) {
	callback = app;
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
