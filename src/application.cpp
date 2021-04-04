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
			// for(int i = 0; i < drumsActive.size(); i++) {
			// 	activeDrums[drumsActive[i]] = true;
			// }
			app->display.showPerformance(drumsActive, 1.0f);
			//Display: Toggle respective drum square and level meter
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
		case SET_DRUM_VOLUME_MODE:
			setdrumvolumemode.previousstate = PERFORMANCE_MODE;
			currentstate = &setdrumvolumemode;
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
