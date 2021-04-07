//application.cpp

#include "application.hpp"

using namespace drumpi;


//States

PerformanceMode::PerformanceMode() {
	label = PERFORMANCE_MODE;
}

void PerformanceMode::interpretKeyPress(ApplicationCallback* appc, int key) {
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
			
		case KEY_M:
			//Display: Show S to indicate mode change
			app->setState(SEQUENCER_MODE);	//change state to SequencerMode
			break;
	
		case KEY_COMMA:
			// Decrease master volume
			app->playbackEngine.volumeDown();
			//Display: Show new master volume
			break;
		case KEY_DOT:
			// Increase master volume
			app->playbackEngine.volumeUp();
			//Display: Show new master volume
			break;
		
		case KEY_V:
			app->setState(SET_DRUM_VOLUME_MODE);	//change state to SetDrumVolumeMode
			break;
	}
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

void SequencerMode::interpretKeyPress(ApplicationCallback* appc, int key) {
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

		case KEY_M:
			//Display: switch to performance display mode
			//stop sequencer before switching to PerformanceMode
			app->seqClocker->stop();
			app->seq->reset(false);
			app->setState(PERFORMANCE_MODE);	//change state to PerformanceMode
			break;

		case KEY_COMMA:
			// Decrease master volume
			app->playbackEngine.volumeDown();
			//Display: updated master volume
			break;
		case KEY_DOT:
			// Increase master volume
			app->playbackEngine.volumeUp();
			//Display: updated master volume
			break;

		case KEY_T:
			app->setState(SET_TEMPO_MODE);	//change state to SetTempoMode
			break;
		case KEY_V:
			app->setState(SET_DRUM_VOLUME_MODE);	//change state to SetDrumVolumeMode
			break;
	}
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


SetTempoMode::SetTempoMode() {
	label = SET_TEMPO_MODE;
}

void SetTempoMode::interpretKeyPress(ApplicationCallback* appc, int key) {
	Application* app = static_cast<Application*>(appc);
	switch (key) {
		case KEY_DOT:
			//increase tempo
			app->seqClocker->setRateBPM(app->seqClocker->getRateBPM() + 20);
			break;
		case KEY_COMMA:
			//decrease tempo
			app->seqClocker->setRateBPM(app->seqClocker->getRateBPM() - 20);
			break;
			
		case KEY_T:
		case KEY_BACKSPACE:
			// Exit SetTempoMode
			app->setState(SEQUENCER_MODE);	//change state to SequencerMode
			break;
	}
}

void SetTempoMode::updateDisplay(ApplicationCallback* appc) {

}


SetDrumVolumeMode::SetDrumVolumeMode() {
	label = SET_DRUM_VOLUME_MODE;
	drumselected = interpretDrumKey(KEY_A);	//default drum A
	previousstate = PERFORMANCE_MODE;	//default previous state
}

void SetDrumVolumeMode::interpretKeyPress(ApplicationCallback *appc, int key) {
	Application* app = static_cast<Application*>(appc);
	switch (key) {
		case KEY_DOT:
			// Increase selected drum's volume
			app->playbackEngine.volumeUp(drumselected);
			// Trigger selected drum for user reference
			app->playbackEngine.trigger(drumselected);
			break;
		case KEY_COMMA:
			// Decrease selected drum's volume
			app->playbackEngine.volumeDown(drumselected);
			// Trigger selected drum for user reference
			app->playbackEngine.trigger(drumselected);
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
			break;

		case KEY_V:
		case KEY_BACKSPACE:
			// Exit SetDrumVolumeMode
			app->setState(previousstate);
			break;
	}
}

void SetDrumVolumeMode::updateDisplay(ApplicationCallback* appc) {

}


//Application

Application::Application() {
	currentstate = &performancemode;
	kbdThread.kbdIn.connectCallback(this);

	// Jack client
	audioEngine.reset(new audio::JackClient("DrumPi"));

	// Get the PlaybackEngine to load the audio samples for bank 1
	playbackEngine.loadBank(1, audio::SOURCE_PREGENERATED);

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
	currentstate->interpretKeyPress(this, key);
}

void Application::setState(stateLabel_t newstate) {
	switch (newstate) {
		case PERFORMANCE_MODE:
			currentstate = &performancemode;
			//switch display to performance mode
			break;
		case SEQUENCER_MODE:
			currentstate = &sequencermode;
			sequencermode.currentpage = 0;	//switch to default page
			sequencermode.currentdrum = currentstate->interpretDrumKey(KEY_A);	//switch to default drum A
			//switch display to sequencer mode
			break;
		case SET_TEMPO_MODE:
			currentstate = &settempomode;
			break;
		case SET_DRUM_VOLUME_MODE:
			if (currentstate == &sequencermode) {
				setdrumvolumemode.previousstate = SEQUENCER_MODE;
				currentstate = &setdrumvolumemode;
			} else if (currentstate == &performancemode) {
				setdrumvolumemode.previousstate = PERFORMANCE_MODE;
				currentstate = &setdrumvolumemode;
			}
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

	app->currentstate->updateDisplay(appc);
}
