//application.cpp

#include "application.hpp"

using namespace drumpi;


//States

PerformanceMode::PerformanceMode() {
	label = "performancemode";
}

void PerformanceMode::interpretKeyPress(ApplicationCallback* app, int key) {
	switch (key) {
		case KEY_A:
			//trigger drum sound
			break;
		case KEY_M:
			app->setState(1);	//change state to SequencerMode
			break;
	}
}

SequencerMode::SequencerMode() {
	label = "sequencermode";
}

void SequencerMode::interpretKeyPress(ApplicationCallback* app, int key) {
	switch (key) {
		case KEY_A:
			//change state to SetSequence
			break;
		case KEY_M:
			app->setState(0);	//change state to PerformanceMode
			break;
	}
}


//Application

Application::Application() {
	currentstate = &performancemode;
}

void Application::run() {
	kbdThread.start();

	while(1) {
		if (kbdThread.kbdIn.keyPressedFlag == 1) {
			currentstate->interpretKeyPress(this, kbdThread.kbdIn.keyPressed);
			kbdThread.kbdIn.keyPressedFlag = 0;
		}
	}
}

void Application::setState(int newstate) {
	switch (newstate) {
		case 0:
			currentstate = &performancemode;
			break;
		case 1:
			currentstate = &sequencermode;
	}
}
