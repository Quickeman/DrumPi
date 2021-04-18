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
	
/*! \ref clock::Metronome derived class to clock a \ref Display. */
class DisplayClock : public clock::Clock {
public:
	/*! Constructor.
	Sets the Application to be clocked.
	\param a \ref Application object to update. */
	DisplayClock(ApplicationCallback* a);

	/*! Override the tick method.
	Clocks the \ref Application. */
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
	\param a \ref Application object to be clocked. */
	DisplayDelay(ApplicationCallback* a);

	/*! Override the tick method.
	Clocks the \ref Application. */
	void trigger() override;

private:

	/*! Pointer to the `Application` object to be clocked. */
	ApplicationCallback* appc = nullptr;

};


/*! Abstract state class. */
class State {
public:
	/*! Label describing state type. */
	stateLabel_t label;

	/*! Virtual function to be overridden by derived class. */
	virtual bool interpretKeyPress(ApplicationCallback* appc, int key) = 0;
	
	/*! Virtual function to be overridden by derived class. */
	virtual void updateDisplay(ApplicationCallback* appc) = 0;
	
	/*! Interprets drum keys and returns a drum ID.
	 * \param key Keypress detected by \ref KeyboardInput class.
	 */
    drumID_t interpretDrumKey(int key);
};


/*! Performance mode state. */
class PerformanceMode : public State {
public:
	/*! Constructor */
	PerformanceMode();

	/*! 
	 * \brief Performs an action depending on the key pressed.
	 * 
	 * This method is called by the \ref Application
	 * when a keyboard event occurs and the application is in
	 * performance mode.
	 * @param appc Callback to the main \ref Application.
	 * @param key The keypress detected.
	 */
	bool interpretKeyPress(ApplicationCallback* appc, int key) override;

	void updateDisplay(ApplicationCallback* appc) override;

};


/*! Sequencer mode state. */
class SequencerMode : public State {
public:
	/*! Constructor */
	SequencerMode();

	/*!
	 * \brief Performs an action depending on the key pressed.
	 * 
	 * This method is called by the \ref Application
	 * when a keyboard event occurs and the application is in
	 * sequencer mode.
	 * @param appc Callback to the main \ref Application.
	 * @param key The keypress detected.
	 */
	bool interpretKeyPress(ApplicationCallback* appc, int key) override;

	void updateDisplay(ApplicationCallback* appc) override;

	/*! Drum currently being set in sequencer. */
	drumID_t currentdrum;
	
	/*!
	 * \brief Page currently displayed on ZeroSeg.
	 * 
	 * Either page 1 (beats 1-8) or page 2 (beats 9-16).
	 */
	int currentpage;
};


/*! Set tempo in this state. */
class SetTempoMode : public State {
public:
	/*! Constructor */
	SetTempoMode();

	/*!
	 * \brief Performs an action depending on the key pressed.
	 * 
	 * This method is called by the \ref Application
	 * when a keyboard event occurs and the application is in
	 * SetTempoMode.
	 * @param appc Callback to the main \ref Application.
	 * @param key The keypress detected.
	 */
	bool interpretKeyPress(ApplicationCallback* appc, int key) override;

	void updateDisplay(ApplicationCallback* appc) override;

private:
	/*! Step size of the tempo inc/decrements. */
	const int bpmStep = 8;

	/*! Minimum BPM. */
	const int minBPM = 38 + bpmStep;
};


/*! Set the master volume in this state (default). */
class SetMasterVolumeMode : public State {
public:
	/*! Constructor. */
	SetMasterVolumeMode();

	/*!
	 * \brief Performs an action depending on the key pressed.
	 * 
	 * This method is called by the \ref Application
	 * when the applicaton is in either performance or sequencer mode
	 * and . or , are pressed.
	 * @param appc Callback to the main \ref Application.
	 * @param key The keypress detected.
	 */
	bool interpretKeyPress(ApplicationCallback* appc, int key) override;

	void updateDisplay(ApplicationCallback* appc) override;
};


/*! Set individual drum volumes in this state. */
class SetDrumVolumeMode : public State {
public:
	/*! Constructor */
	SetDrumVolumeMode();

	/*!
	 * \brief Performs an action depending on the key pressed.
	 * 
	 * This method is called by the \ref Application
	 * when a keyboard event occurs and the application is in
	 * SetDrumVolumeMode.
	 * @param appc Callback to the main \ref Application.
	 * @param key The keypress detected.
	 */
	bool interpretKeyPress(ApplicationCallback* appc, int key) override;

	void updateDisplay(ApplicationCallback* appc) override;

private:
	/*! Drum volume currently selected to be modified. */
	drumID_t drumselected;

	/*! Whether to trigger the sounds on volume change. */
	bool triggerDrums;
};


/*! Load different banks of drums in this state. */
class SetDrumBankMode : public State {
public:
	/*! Constructor. */
	SetDrumBankMode();

	/*!
	 * \brief Performs an action depending on the key pressed.
	 * 
	 * This method is called by the \ref Application
	 * when a keyboard event occurs and the application is in
	 * SetDrumBankMode.
	 * @param appc Callback to the main \ref Application.
	 * @param key The keypress detected.
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


/*! 
 * \brief Main application.
 * 
 * This is the main application for the DrumPi program.
 * Its \ref setup and \ref run methods are called when the application
 * is started.
 */
class Application : public ApplicationCallback {
public:
	
	/*! Constructor */
	Application();

	/*! \brief Sets up the application. 
	 * 
	 * This method is called on startup to perform various set up tasks,
	 * including connecting the \ref Application to the \ref KeyboardInput
	 * as a callback, resetting the sequencer and display,
	 * and loading the drum sample bank.
	 */
	void setup();

	/*! \brief Runs the application.
	 * 
	 * This method is called on startup after setup has been
	 * performed, starting the audio engine, the display refresh clock,
	 * and creating the keyboard thread.
	 */
	void run();
	
	/*! 
	 * This method is called by \ref KeyboardInput when a keyboard event occurs.
	 * 
	 * @param key The keypress detected.
	 */
	void interpretKeyPress(int key) override;

	/*! Changes the current state. */
	void setState(stateLabel_t newstate) override;


	/*! Instance of \ref PerformanceMode state. */
	PerformanceMode performancemode;

	/*! Instance of \ref SequencerMode state. */
	SequencerMode sequencermode;

	/*! Pointer to the current mode instance. */
	State* mode;
	

	/*! Instance of \ref SetMasterVolumeMode state. */
	SetMasterVolumeMode setMasterVolumeMode;

	/*! Instance of \ref SetTempoMode state. */
	SetTempoMode settempomode;

	/*! Instance of \ref SetDrumVolumeMode state. */
	SetDrumVolumeMode setdrumvolumemode;

	/*! Instance of \ref SetDrumBankMode state. */
	SetDrumBankMode setDrumBankMode;

	/*! Pointer to the current sub-mode instance. */
	State* subMode;


	/*! Pointer to the state to be displayed. */
	State* displayState;


	/*! Instance of \ref KeyboardThread class. */
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
