//application.cpp

#include "application.hpp"

using namespace drumpi;


//States

PerformanceMode::PerformanceMode() {
	label = PERFORMANCE_MODE;
}

void PerformanceMode::interpretKeyPress(ApplicationCallback* appc, int key) {
	Application* app = static_cast<Application*>(appc);
	std::vector<drumID_t> drumsActive;
	std::vector<bool> activeDrums;
	activeDrums.resize(8);
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
			drumsActive = app->playbackEngine.getActive();
			for(int i = 0; i < drumsActive.size(); i++) {
				activeDrums[drumsActive[i]] = true;
			}
			app->display.showPerformance(activeDrums, 0.5f);
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


SequencerMode::SequencerMode() {
	label = SEQUENCER_MODE;
	currentdrum = interpretDrumKey(KEY_A);	//default drum A
	currentpage = 1;	//default page 1 (beats 1-8)
	playing = false;	//sequencer stopped by default
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
			// Trigger the drum sound
			app->playbackEngine.trigger(interpretDrumKey(key));
			//Display: Toggle corresponding DP
			//change currentdrum to respective drum
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
			// Insert currentdrum into relevant beat
			break;
		
		case KEY_TAB:
			currentpage++;
			if (currentpage > 2) currentpage = 1;
			// Display relevant beats for currentdrum
			break;
			
		case KEY_SPACE:
			// Toggle play/pause sequence display
			playing = !playing;	//Toggle play/pause
			break;

		case KEY_M:
			//Display: switch to performance display mode
			//stop sequencer before switching to PerformanceMode
			playing = false;
			app->setState(PERFORMANCE_MODE);	//change state to PerformanceMode
			break;

		case KEY_COMMA:
			//Display: updated master volume
			//decrease master volume
			break;
		case KEY_DOT:
			//Display: updated master volume
			//increase master volume
			break;

		case KEY_T:
			app->setState(SET_TEMPO_MODE);	//change state to SetTempoMode
			break;
		case KEY_V:
			app->setState(SET_DRUM_VOLUME_MODE);	//change state to SetDrumVolumeMode
			break;
	}
}


SetTempoMode::SetTempoMode() {
	label = SET_TEMPO_MODE;
}

void SetTempoMode::interpretKeyPress(ApplicationCallback* appc, int key) {
	Application* app = static_cast<Application*>(appc);
	switch (key) {
		case KEY_DOT:
			//increase tempo (should tempo variable be a member of SetTempoMode or Application??)
			break;
		case KEY_COMMA:
			//decrease tempo
			break;
			
		case KEY_T:
		case KEY_ESC:
			// Exit SetTempoMode
			app->setState(SEQUENCER_MODE);	//change state to SequencerMode
			break;
	}
}


SetDrumVolumeMode::SetDrumVolumeMode() {
	label = SET_DRUM_VOLUME_MODE;
	drumselected = interpretDrumKey(KEY_A);	//default drum A
	previousstate = PERFORMANCE_MODE;	//default previous state
}

void SetDrumVolumeMode::interpretKeyPress(ApplicationCallback *appc, int key) {
	Application* app = static_cast<Application*>(appc);
	drumID_t drum = interpretDrumKey(key);
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
			// Trigger the drum sound
			app->playbackEngine.trigger(drum);
			drumselected = drum;	//set drumselected to respective drum
			break;

		case KEY_V:
		case KEY_ESC:
			// Exit SetDrumVolumeMode
			app->setState(previousstate);
			break;
	}
}


//Application

Application::Application() {
	currentstate = &performancemode;
	kbdThread.kbdIn.connectCallback(this);

	// Jack client
	audioEngine.reset(new audio::JackClient("DrumPi"));

	// Get the PlaybackEngine to load all of the audio samples
	for (int i = 0; i < NUM_DRUMS; i++) {
		playbackEngine.setSource((drumID_t)i, audio::SOURCE_PREGENERATED);
	}

	// // Sequencer
	// seq.reset(new Sequencer(16));
	// // SequencerClock
	// seqClocker.setSequencer(seq);
}

void Application::run() {
	// Start the audio stream
	audioEngine->start(playbackEngine);

	kbdThread.start();

	while(running) {}

	kbdThread.stop();

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
			sequencermode.currentpage = 1;	//switch to default page
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
			return TOM_1_DRUM;
			break;
		case KEY_S:
			return TOM_2_DRUM;
			break;
		case KEY_D:
			return SNARE_DRUM;
			break;
		case KEY_F:
			return KICK_DRUM;
			break;
		case KEY_J:
			return CLAP_DRUM;
			break;
		case KEY_K:
			return HI_HAT_CLOSED;
			break;
		case KEY_L:
			return HI_HAT_OPEN;
			break;
		case KEY_SEMICOLON:
			return CYMBAL_DRUM;
			break;
	}
}
