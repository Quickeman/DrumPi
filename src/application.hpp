//application.hpp

#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>
#include "audio.hpp"
#include "sequencer.hpp"
#include "keyboardthread.hpp"

namespace drumpi {

class ApplicationCallback {
public:
	virtual void setState(int newstate) = 0;
};


/*! Abstract state class */
class State {
public:
	std::string label;
	virtual void interpretKeyPress(ApplicationCallback* app, int key) = 0;
};

/*! Performance mode state */
class PerformanceMode : public State {
public:
	PerformanceMode();
	void interpretKeyPress(ApplicationCallback* app, int key) override;
};

/*! Sequencer mode state */
class SequencerMode : public State {
public:
	SequencerMode();
	void interpretKeyPress(ApplicationCallback* app, int key) override;
};


/*! Main application */
class Application : public ApplicationCallback {
public:
	
	/*! Constructor */
	Application();

	void setup();

	void run();

	void setState(int newstate) override;
	
	State* currentstate;
	PerformanceMode performancemode;
	SequencerMode sequencermode;

	keyboard::KeyboardThread kbdThread;

};

}	// namespace drumpi

#endif	// define APPLICATION_H
