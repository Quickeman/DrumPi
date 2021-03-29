//application.hpp

#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>
#include <memory>

#include "audio.hpp"
#include "playback.hpp"
#include "display.hpp"
#include "sequencer.hpp"
#include "keyboardthread.hpp"

namespace drumpi {


/*! Abstract state class */
class State {
public:
	/*! Label describing state type */
	stateLabel_t label;

	/*! Virtual function to be overridden by derived class */
	virtual void interpretKeyPress(ApplicationCallback* appc, int key) = 0;
	
	/*! Interprets drum keys and returns a drum ID */
    drumID_t interpretDrumKey(int key);
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
	 * @param appc Callback to the main application
	 * @param key The keypress detected
	 */
	void interpretKeyPress(ApplicationCallback* appc, int key) override;
};

/*! Set individual drum volumes in this state */
class SetDrumVolumeMode : public State {
public:
	/*! Constructor */
	SetDrumVolumeMode();

	/*!
	 * \brief Method to perform action depending on key pressed.
	 * 
	 * Action performed is unique to SetDrumVolumeMode.
	 * @param appc Callback to the main application
	 * @param key The keypress detected
	 */
	void interpretKeyPress(ApplicationCallback* appc, int key) override;

	/*! Variable storing the previous state of the application */
	stateLabel_t previousstate;

private:
	/*! Drum volume currently selected to be modified */
	drumID_t drumselected;
};


/*! Main application */
class Application : public ApplicationCallback {
public:
	
	/*! Constructor */
	Application();

	/*! Method to run the application */
	void run();
	
	/*! 
	 * Method called by keyboard input when a keyboard event occurs.
	 * 
	 * @param key The keypress detected
	 */
	void interpretKeyPress(int key) override;

	/*! Method to change the current state */
	void setState(stateLabel_t newstate) override;

	/*! Pointer to current state instance */
	State* currentstate;

	/*! Instance of PerformanceMode state */
	PerformanceMode performancemode;

	/*! Instance of SetDrumVolumeMode state */
	SetDrumVolumeMode setdrumvolumemode;

	/*! Instance of KeyboardThread class */
	KeyboardThread kbdThread;

	/*! AudioEngine object. */
	std::unique_ptr<audio::JackClient> audioEngine = nullptr;

	/*! PlaybackEngine object. */
	audio::PlaybackEngine playbackEngine;

	/*! Display object. */
	Display display;
};

}	// namespace drumpi

#endif	// define APPLICATION_H
