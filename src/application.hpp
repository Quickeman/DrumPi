//application.hpp

#ifndef APPLICATION_H
#define APPLICATION_H

#include "audio.hpp"
#include "sequencer.hpp"
#include "keyboardthread.hpp"

namespace drumpi {

class Application {

public:
	
	Application();

	void setup();

	void run();

	void interpretKeyPress();

};

}	// namespace drumpi

#endif	// define APPLICATION_H
