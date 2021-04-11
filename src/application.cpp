//application.cpp

#include <iostream>

#include "application.hpp"

using namespace drumpi;


//States

PerformanceMode::PerformanceMode() {
	label = PERFORMANCE_MODE;
}

bool PerformanceMode::interpretKeyPress(ApplicationCallback* appc, int key) {
	Application* app = static_cast<Application*>(appc);
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

			//Display: Toggle respective drum square and level meter
			break;
	}

	return false;
}

void PerformanceMode::updateDisplay(ApplicationCallback* appc) {
	Application* app = static_cast<Application*>(appc);

	std::vector<drumID_t> drumsActive;
	drumsActive = app->playbackEngine.getActive();
	app->display.setPerformance(drumsActive, 1.0f, true);
}


SequencerMode::SequencerMode() {
	label = SEQUENCER_MODE;
	currentdrum = interpretDrumKey(KEY_A);	//default drum A
	currentpage = 0;	//default page 1 (beats 1-8)
	//Display: Show tom 1 drum page 1 sequence
}

bool SequencerMode::interpretKeyPress(ApplicationCallback* appc, int key) {
	Application* app = static_cast<Application*>(appc);
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
			//Display: Toggle corresponding DP
			//display currentpage for respective drum
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
			break;
		
		case KEY_TAB:
			currentpage++;
			if (currentpage > 1) currentpage = 0;
			// Display relevant beats for currentdrum
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
			// Toggle play/pause sequence display
			break;
	}

	return false;
}

void SequencerMode::updateDisplay(ApplicationCallback* appc) {
	Application* app = static_cast<Application*>(appc);

	//std::vector<drumID_t> activeDrums;
	//app->display.setPerformance(activeDrums, 0.0f, true);

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
			app->seqClocker->setRateBPM(app->seqClocker->getRateBPM() + 20);
			actionFlag = true;
			break;
		case KEY_COMMA:
			//decrease tempo
			app->seqClocker->setRateBPM(app->seqClocker->getRateBPM() - 20);
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
			// Set the display to show the master volume for a few seconds
			// something like:
			// app->displayState = setMasterVolumeMode
			// displayDelay.setTime(3) // displayDelay being a clock::Timer
			// displayDelay.start(); // will change displayState back to perf/seq mode on trigger
			actionFlag = true;
			break;
		case KEY_DOT:
			// Master volume up
			app->playbackEngine.volumeUp();
			// Set the display to show the master volume for a few seconds
			// See above for example pseudocode
			actionFlag = true;
			break;
	}

	return actionFlag;
}

void SetMasterVolumeMode::updateDisplay(ApplicationCallback* appc) {

}


// SetDrumVolumeMode

SetDrumVolumeMode::SetDrumVolumeMode() {
	label = SET_DRUM_VOLUME_MODE;
	drumselected = interpretDrumKey(KEY_A);	//default drum A
}

bool SetDrumVolumeMode::interpretKeyPress(ApplicationCallback *appc, int key) {
	Application* app = static_cast<Application*>(appc);
	bool actionFlag = false;
	switch (key) {
		case KEY_DOT:
			// Increase selected drum's volume
			app->playbackEngine.volumeUp(drumselected);
			// Trigger selected drum for user reference
			app->playbackEngine.trigger(drumselected);
			actionFlag = true;
			break;
		case KEY_COMMA:
			// Decrease selected drum's volume
			app->playbackEngine.volumeDown(drumselected);
			// Trigger selected drum for user reference
			app->playbackEngine.trigger(drumselected);
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
	}

	return actionFlag;
}

void SetDrumVolumeMode::updateDisplay(ApplicationCallback* appc) {
	Application* app = static_cast<Application*>(appc);
	app->display.setDrumVolume(int(100*(app->playbackEngine.getVolume(drumselected))), drumselected, true);
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
	if (!subMode->interpretKeyPress(this, key)) {
		mode->interpretKeyPress(this, key);
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
	switch (newstate) {
		case PERFORMANCE_MODE:
			mode = &performancemode;
			subMode = &setMasterVolumeMode;
			displayState = mode;
			//switch display to performance mode
			break;
		case SEQUENCER_MODE:
			mode = &sequencermode;
			subMode = &setMasterVolumeMode;
			displayState = mode;
			sequencermode.currentpage = 0;	//switch to default page
			//switch display to sequencer mode
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


// DisplayClock class

DisplayClock::DisplayClock(ApplicationCallback* a) {
    setRate(33); //ms
    appc = a;
}

void DisplayClock::tick() {
	Application* app = static_cast<Application*>(appc);

	app->displayState->updateDisplay(appc);
}
