//application.hpp

#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>
#include <memory>

#include "applicationcallback.hpp"
#include "audio.hpp"
#include "playback.hpp"
#include "display.hpp"
#include "sequencer.hpp"
#include "keyboardthread.hpp"

namespace drumpi {
	
/*! \ref Metronome derived class to clock a \ref Display. */
class DisplayClock : public clock::Clock {
public:
	/*! Constructor.
	Sets the Application to be clocked.
	\param s \ref Application object to be clocked. */
	DisplayClock(ApplicationCallback* a);

	/*! Override the tick method.
	Clocks the \ref Application given to \ref setApplication. */
	void tick() override;

private:

	/*! Pointer to the `Application` object to be clocked. */
	ApplicationCallback* appc = nullptr;

};

/*! \ref Timer derived class to clock master volume display timeout. */
class DisplayDelay : public clock::Timer {
public:
	/*! Constructor.
	Sets the Application to be clocked.
	\param s \ref Application object to be clocked. */
	DisplayDelay(ApplicationCallback* a);

	/*! Override the tick method.
	Clocks the \ref Application given to \ref setApplication. */
	void trigger() override;

private:

	/*! Pointer to the `Application` object to be clocked. */
	ApplicationCallback* appc = nullptr;

};


/*! Abstract state class */
class State {
public:
	/*! Label describing state type */
	stateLabel_t label;

	/*! Virtual function to be overridden by derived class */
	virtual bool interpretKeyPress(ApplicationCallback* appc, int key) = 0;
	
	/*! Virtual function to be overridden by derived class */
	virtual void updateDisplay(ApplicationCallback* appc) = 0;
	
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
	bool interpretKeyPress(ApplicationCallback* appc, int key) override;

	void updateDisplay(ApplicationCallback* appc) override;

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
	 * @param appc Callback to the main application
	 * @param key The keypress detected
	 */
	bool interpretKeyPress(ApplicationCallback* appc, int key) override;

	void updateDisplay(ApplicationCallback* appc) override;

	/*! Drum currently being set in sequencer */
	drumID_t currentdrum;
	/*!
	 * \brief Page currently displayed on ZeroSeg.
	 * 
	 * Either page 1 (beats 1-8) or page 2 (beats 9-16)
	 */
	int currentpage;
};


/*! Set tempo in this state */
class SetTempoMode : public State {
public:
	/*! Constructor */
	SetTempoMode();

	/*!
	 * \brief Method to perform action depending on key pressed.
	 * 
	 * Action performed is unique to SetTempoMode.
	 * @param appc Callback to the main application
	 * @param key The keypress detected
	 */
	bool interpretKeyPress(ApplicationCallback* appc, int key) override;

	void updateDisplay(ApplicationCallback* appc) override;

private:
	/*! Step size of the tempo inc/decrements. */
	const int bpmStep = 20;

	/*! Minimum BPM. */
	const int minBPM = 28 + bpmStep;
};


/*! Set the master volume in this state (default) */
class SetMasterVolumeMode : public State {
public:
	/*! Constructor. */
	SetMasterVolumeMode();

	/*!
	 * \brief Method to perform action depending on key pressed.
	 * 
	 * Action performed is unique to SetMasterVolumeMode.
	 * @param appc Callback to the main application
	 * @param key The keypress detected
	 */
	bool interpretKeyPress(ApplicationCallback* appc, int key) override;

	void updateDisplay(ApplicationCallback* appc) override;
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
	bool interpretKeyPress(ApplicationCallback* appc, int key) override;

	void updateDisplay(ApplicationCallback* appc) override;

private:
	/*! Drum volume currently selected to be modified */
	drumID_t drumselected;
};


/*! Load different banks of drums in this state. */
class SetDrumBankMode : public State {
public:
	/*! Constructor. */
	SetDrumBankMode();

	/*!
	 * \brief Method to perform action depending on key pressed.
	 * 
	 * Action performed is unique to SetDrumBankMode.
	 * @param appc Callback to the main application
	 * @param key The keypress detected
	 */
	bool interpretKeyPress(ApplicationCallback* appc, int key) override;

	void updateDisplay(ApplicationCallback* appc) override;

	/*! Returns the current bank's ID. */
	int getBank();

private:
	/*! Current bank selected. */
	int bank;
	/*! The last bank successfully loaded. */
	int safeBank;
};


/*! Main application */
class Application : public ApplicationCallback {
public:
	
	/*! Constructor */
	Application();

	/*! Method to set up the application */
	void setup();

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


	/*! Instance of PerformanceMode state */
	PerformanceMode performancemode;

	/*! Instance of SequencerMode state */
	SequencerMode sequencermode;

	/*! Pointer to current mode instance */
	State* mode;
	

	/*! Instance of SetMasterVolumeMode state. */
	SetMasterVolumeMode setMasterVolumeMode;

	/*! Instance of SetTempoMode state */
	SetTempoMode settempomode;

	/*! Instance of SetDrumVolumeMode state */
	SetDrumVolumeMode setdrumvolumemode;

	/*! Instance of SetDrumBankMode state. */
	SetDrumBankMode setDrumBankMode;

	/*! Pointer to current sub-mode instance */
	State* subMode;


	/*! Pointer to the state to be displayed. */
	State* displayState;


	/*! Instance of KeyboardThread class */
	KeyboardThread kbdThread;

	/*! AudioEngine object. */
	std::unique_ptr<audio::JackClient> audioEngine = nullptr;
	
	/*! DisplayClock object. */
	std::unique_ptr<DisplayClock> displayClock = nullptr;

	/*! DisplayTimer object. */
	std::unique_ptr<DisplayDelay> displayDelay = nullptr;

	/*! PlaybackEngine object. */
	audio::PlaybackEngine playbackEngine;

	/*! Display object. */
	Display display;

	/*! Sequencer object. */
	std::shared_ptr<Sequencer> seq = nullptr;

	/*! SequencerClock object used to clock the Sequencer. */
	std::unique_ptr<SequencerClock> seqClocker = nullptr;

};

} // namespace drumpi

#endif	// define APPLICATION_H
