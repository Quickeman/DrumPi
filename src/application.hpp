//application.hpp

#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>
#include "audio.hpp"
#include "sequencer.hpp"
#include "keyboardthread.hpp"

namespace drumpi {

/* Abstract application callback class */
class ApplicationCallback {
public:
	/*! Virtual function to be overridden by derived class */
	virtual void setState(int newstate) = 0;
};


/*! Abstract state class */
class State {
public:
	/*! Label describing state type */
	std::string label;

	/*! Virtual function to be overridden by derived class */
	virtual void interpretKeyPress(ApplicationCallback* app, int key) = 0;
};

/*! Performance mode state */
class PerformanceMode : public State {
public:
	/*! Constructor */
	PerformanceMode();

	/*! 
	 * \brief Method to perform action depending on key pressed.
	 * 
	 * Action performed is unique to performance mode.
	 */
	void interpretKeyPress(ApplicationCallback* app, int key) override;
};

/*! Sequencer mode state */
class SequencerMode : public State {
public:
	/*! Constructor */
	SequencerMode();

	/*!
	 * \brief Method to perform action depending on key pressed.
	 * 
	 * Action performed is unique to sequencer mode.
	 */
	void interpretKeyPress(ApplicationCallback* app, int key) override;
};


/*! Main application */
class Application : public ApplicationCallback {
public:
	
	/*! Constructor */
	Application();

	/*! Method to run the application */
	void run();

	/*! Method to change the current state */
	void setState(int newstate) override;
	
	/*! Pointer to current state instance */
	State* currentstate;

	/*! Instance of performance mode state */
	PerformanceMode performancemode;

	/*! Instance of sequencer mode state */
	SequencerMode sequencermode;

	/*! Instance of KeyboardThread class */
	keyboard::KeyboardThread kbdThread;

};

}	// namespace drumpi

#endif	// define APPLICATION_H
