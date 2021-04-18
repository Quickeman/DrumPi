//application.cpp

#include <iostream>

#include "application.hpp"

using namespace drumpi;

// DisplayClock class

DisplayClock::DisplayClock(ApplicationCallback* a) {
    setRate(33); //ms
    appc = a;
}

void DisplayClock::tick() {
	Application* app = static_cast<Application*>(appc);

	app->displayState->updateDisplay(appc);
}

// Display Delay class

DisplayDelay::DisplayDelay(ApplicationCallback* a) {
	setTime(2000);
    appc = a;
}

void DisplayDelay::trigger() {
	Application* app = static_cast<Application*>(appc);
	app->displayState = app->mode; // Reset to primary display mode after timeout
}

//States

drumID_t State::interpretDrumKey(int key) {
	switch (key) {
		case KEY_A : default :
			return DRUM_1;
			break;
		case KEY_S:
			return DRUM_2;
			break;
		case KEY_D:
			return DRUM_3;
			break;
		case KEY_F:
			return DRUM_4;
			break;
		case KEY_J:
			return DRUM_5;
			break;
		case KEY_K:
			return DRUM_6;
			break;
		case KEY_L:
			return DRUM_7;
			break;
		case KEY_SEMICOLON:
			return DRUM_8;
			break;
	}
}


// PerformanceMode

PerformanceMode::PerformanceMode() {
	label = PERFORMANCE_MODE;
}

bool PerformanceMode::interpretKeyPress(ApplicationCallback* appc, int key) {
	Application* app = static_cast<Application*>(appc);
	bool actionFlag = false;
	switch (key) {
		case KEY_A:
		case KEY_S:
		case KEY_D:
		case KEY_F:
		case KEY_J:
		case KEY_K:
		case KEY_L:
		case KEY_SEMICOLON:
			// Trigger the drum sound
			app->playbackEngine.trigger(interpretDrumKey(key));
			actionFlag = true;
			break;
	}

	return actionFlag;
}

void PerformanceMode::updateDisplay(ApplicationCallback* appc) {
	Application* app = static_cast<Application*>(appc);

	std::vector<drumID_t> drumsActive;
	drumsActive = app->playbackEngine.getActive();
	app->display.setPerformance(drumsActive, 1.0f, true);
}


// SequencerMode

SequencerMode::SequencerMode() {
	label = SEQUENCER_MODE;
	currentdrum = interpretDrumKey(KEY_A);	//default drum A
	currentpage = 0;	//default page 1 (beats 1-8)
}

bool SequencerMode::interpretKeyPress(ApplicationCallback* appc, int key) {
	Application* app = static_cast<Application*>(appc);
	bool actionFlag = false;
	switch (key) {
		case KEY_A:
		case KEY_S:
		case KEY_D:
		case KEY_F:
		case KEY_J:
		case KEY_K:
		case KEY_L:
		case KEY_SEMICOLON:
			// Interpret the drum key
			currentdrum = interpretDrumKey(key);
			// Trigger the drum sound
			app->playbackEngine.trigger(currentdrum);
			actionFlag = true;
			break;
		
		case KEY_1:
		case KEY_2:
		case KEY_3:
		case KEY_4:
		case KEY_5:
		case KEY_6:
		case KEY_7:
		case KEY_8:
			// Toggle currentdrum in relevant beat
			app->seq->toggle(
				currentdrum,
				(key - KEY_1) + (currentpage * 8)
			);
			actionFlag = true;
			break;
		
		case KEY_TAB:
			currentpage++;
			if (currentpage > 1) currentpage = 0;
			actionFlag = true;
			break;
			
		case KEY_SPACE:
			// Toggle Sequencer's activity state
			if(app->seqClocker->isActive()) {
				// Stop the Sequencer's clock
				app->seqClocker->stop();
				// Reset the Sequencer to first step, not clearing the sequence
				app->seq->reset(false);
			} else {
				app->seqClocker->start();
			}
			actionFlag = true;
			break;
	}

	return actionFlag;
}

void SequencerMode::updateDisplay(ApplicationCallback* appc) {
	Application* app = static_cast<Application*>(appc);

	std::vector<bool> activeDigits;
	unsigned int step;

	activeDigits = app->seq->getSteps(currentdrum);
	step = app->seq->getStepNum();

	if(app->seqClocker->isActive()) {
		app->display.setPlaybackSeq(activeDigits, step, true);
	}
	else {
		app->display.setStopSeq(activeDigits, currentpage, currentdrum, true);
	}
}


// SetTempoMode

SetTempoMode::SetTempoMode() {
	label = SET_TEMPO_MODE;
}

bool SetTempoMode::interpretKeyPress(ApplicationCallback* appc, int key) {
	Application* app = static_cast<Application*>(appc);
	bool actionFlag = false;
	switch (key) {
		case KEY_DOT:
			//increase tempo
			app->seqClocker->setRateBPM(app->seqClocker->getRateBPM() + bpmStep);
			actionFlag = true;
			break;
		case KEY_COMMA:
			//decrease tempo
			if (app->seqClocker->getRateBPM() > minBPM) {
				app->seqClocker->setRateBPM(app->seqClocker->getRateBPM() - bpmStep);
			}
			actionFlag = true;
			break;
	}

	return actionFlag;
}

void SetTempoMode::updateDisplay(ApplicationCallback* appc) {
	Application* app = static_cast<Application*>(appc);
	app->display.setVal(app->seqClocker->getRateBPM()/4, true);
}


// SetMasterVolumeMode

SetMasterVolumeMode::SetMasterVolumeMode() {
	label = SET_MASTER_VOLUME_MODE;
}

bool SetMasterVolumeMode::interpretKeyPress(ApplicationCallback* appc, int key) {
	Application* app = static_cast<Application*>(appc);
	bool actionFlag = false;
	switch (key) {
		case KEY_COMMA:
			// Master volume down
			app->playbackEngine.volumeDown();
			app->displayState = app->subMode;
			app->displayDelay->start();
			actionFlag = true;
			break;
		case KEY_DOT:
			// Master volume up
			app->playbackEngine.volumeUp();
			app->displayState = app->subMode;
			app->displayDelay->start();
			actionFlag = true;
			break;
	}

	return actionFlag;
}

void SetMasterVolumeMode::updateDisplay(ApplicationCallback* appc) {
	Application* app = static_cast<Application*>(appc);
	app->display.setVal(app->playbackEngine.getVolume(), true);
}


// SetDrumVolumeMode

SetDrumVolumeMode::SetDrumVolumeMode() {
	label = SET_DRUM_VOLUME_MODE;
	drumselected = interpretDrumKey(KEY_A);	//default drum A
	triggerDrums = true;
}

bool SetDrumVolumeMode::interpretKeyPress(ApplicationCallback *appc, int key) {
	Application* app = static_cast<Application*>(appc);
	bool actionFlag = false;
	switch (key) {
		case KEY_DOT:
			// Increase selected drum's volume
			app->playbackEngine.volumeUp(drumselected);
			// Trigger selected drum for user reference
			if (triggerDrums) app->playbackEngine.trigger(drumselected);
			actionFlag = true;
			break;
		case KEY_COMMA:
			// Decrease selected drum's volume
			app->playbackEngine.volumeDown(drumselected);
			// Trigger selected drum for user reference
			if (triggerDrums) app->playbackEngine.trigger(drumselected);
			actionFlag = true;
			break;
		
		case KEY_A:
		case KEY_S:
		case KEY_D:
		case KEY_F:
		case KEY_J:
		case KEY_K:
		case KEY_L:
		case KEY_SEMICOLON:
			// Interpret the drum key
			drumselected = interpretDrumKey(key);
			// Trigger the drum sound
			app->playbackEngine.trigger(drumselected);
			actionFlag = true;
			break;

		case KEY_Z:
			triggerDrums = !triggerDrums;
			break;
	}

	return actionFlag;
}

void SetDrumVolumeMode::updateDisplay(ApplicationCallback* appc) {
	Application* app = static_cast<Application*>(appc);
	app->display.setDrumVolume(app->playbackEngine.getVolume(drumselected), drumselected, true);
}


// SetDrumBankMode

SetDrumBankMode::SetDrumBankMode() {
	// Default bank
	bank = 1;
	safeBank = bank;
	label = SET_DRUM_BANK_MODE;
}

bool SetDrumBankMode::interpretKeyPress(ApplicationCallback* appc, int key) {
	Application* app = static_cast<Application*>(appc);
	audio::sampleSourceStatus_t loadStatus = audio::SOURCE_READY;
	bool actionFlag = false;
	switch (key) {
		case KEY_DOT:
			// Bank up
			bank++;
			// Load the bank
			loadStatus = app->playbackEngine.loadBank(bank, audio::SOURCE_PREGENERATED);
			actionFlag = true;
			break;
		case KEY_COMMA:
			// Bank down
			if (bank > 0) bank--;
			// Load the bank
			loadStatus = app->playbackEngine.loadBank(bank, audio::SOURCE_PREGENERATED);
			actionFlag = true;
			break;
		
		case KEY_A:
		case KEY_S:
		case KEY_D:
		case KEY_F:
		case KEY_J:
		case KEY_K:
		case KEY_L:
		case KEY_SEMICOLON:
			// Trigger the relevant drum sound
			app->playbackEngine.trigger(interpretDrumKey(key));
			actionFlag = true;
			break;
	}

	if (loadStatus != audio::SOURCE_READY) {
		std::cout << std::endl << "Could not load bank " << bank << std::endl;
		std::cout << "Returning to bank " << safeBank << std::endl;
		bank = safeBank;
		app->playbackEngine.loadBank(bank, audio::SOURCE_PREGENERATED);
	} else {
		safeBank = bank;
	}

	return actionFlag;
}

void SetDrumBankMode::updateDisplay(ApplicationCallback* appc) {
	Application* app = static_cast<Application*>(appc);
	app->display.setVal(getBank(), true);
}

int SetDrumBankMode::getBank() {
	return bank;
}


//Application

Application::Application() {
	mode = &performancemode;
	subMode = &setMasterVolumeMode;
	displayState = mode;
	running = true;
}

void Application::setup() {
	// Connect keyboard thread to Application
	kbdThread.kbdIn.connectCallback(this);

	// Jack client
	audioEngine.reset(new audio::JackClient("DrumPi"));

	// Get the PlaybackEngine to load the audio samples for bank 1
	playbackEngine.loadBank(setDrumBankMode.getBank(), audio::SOURCE_PREGENERATED);

	// Sequencer
	seq.reset(new Sequencer(16));
	// SequencerClock
	seqClocker.reset(new SequencerClock(seq, playbackEngine));

	// DisplayClock
	displayClock.reset(new DisplayClock(this));

	// Display Delay timer
	displayDelay.reset(new DisplayDelay(this));	
}	

void Application::run() {
	// Start the audio stream
	audioEngine->start(playbackEngine);

	displayClock->start();

	kbdThread.start();

	while(running) {}

	kbdThread.stop();

	displayClock->stop();

	audioEngine->stop();
}

void Application::interpretKeyPress(int key) {
	bool actionFlag;

	actionFlag = subMode->interpretKeyPress(this, key);
	
	if (!actionFlag) {
		actionFlag = mode->interpretKeyPress(this, key);
		if (actionFlag) setState(mode->label);
	}

	// If any of the mode buttons, setState(selectedMode)
	switch (key) {
		case KEY_BACKSPACE:
			// Go to main mode
			setState(mode->label);
			break;
		
		case KEY_M:
			// Swap between performance and sequencer modes
			if (mode->label == PERFORMANCE_MODE) {
				setState(SEQUENCER_MODE);
			} else {
				seqClocker->stop();
				seq->reset(false);
				setState(PERFORMANCE_MODE);
			}
			break;
		
		case KEY_V:
			if (subMode->label != SET_DRUM_VOLUME_MODE) {
				// If not in setDrumVolumeMode, go to it
				setState(SET_DRUM_VOLUME_MODE);
			} else {
				// otherwise escape to main mode
				setState(mode->label);
			}
			break;

		case KEY_B:
			if (subMode->label != SET_DRUM_BANK_MODE) {
				// If not in setDrumBankMode, go to it
				setState(SET_DRUM_BANK_MODE);
			} else {
				// otherwise escape to main mode
				setState(mode->label);
			}
			break;

		case KEY_T:
			if (mode->label == SEQUENCER_MODE) {
				if (subMode->label != SET_TEMPO_MODE) {
					// If not in setTempoMode and in sequencerMode, go to it
					setState(SET_TEMPO_MODE);
				} else {
					// otherwise escape to main mode
					setState(mode->label);
				}
			}
			break;
	}
}

void Application::setState(stateLabel_t newstate) {
	// Stop display delay timer to prevent display mode switching
	if(displayDelay->isActive()) displayDelay->stop(); 
	switch (newstate) {
		case PERFORMANCE_MODE:
			mode = &performancemode;
			subMode = &setMasterVolumeMode;
			displayState = mode;
			break;
		case SEQUENCER_MODE:
			mode = &sequencermode;
			subMode = &setMasterVolumeMode;
			displayState = mode;
			break;
		case SET_TEMPO_MODE:
			subMode = &settempomode;
			displayState = subMode;
			break;
		case SET_DRUM_VOLUME_MODE:
			subMode = &setdrumvolumemode;
			displayState = subMode;
			break;
		case SET_DRUM_BANK_MODE:
			subMode = &setDrumBankMode;
			displayState = subMode;
			break;
	}
}
