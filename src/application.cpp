//application.cpp

#include "application.hpp"

using namespace drumpi;


//States

PerformanceMode::PerformanceMode() {
	label = PERFORMANCE_MODE;
}

void PerformanceMode::interpretKeyPress(ApplicationCallback* app, int key) {
	switch (key) {
		case KEY_A:
			//Display: Toggle respective drum square and level meter
			//trigger drum sound
			break;
		case KEY_S:
			//Display: Toggle respective drum square and level meter
			//trigger drum sound
			break;
		case KEY_D:
			//Display: Toggle respective drum square and level meter
			//trigger drum sound
			break;
		case KEY_F:
			//Display: Toggle respective drum square and level meter
			//trigger drum sound
			break;
		case KEY_J:
			//Display: Toggle respective drum square and level meter
			//trigger drum sound
			break;
		case KEY_K:
			//Display: Toggle respective drum square and level meter
			//trigger drum sound
			break;
		case KEY_L:
			//Display: Toggle respective drum square and level meter
			//trigger drum sound
			break;
		case KEY_SEMICOLON:
			//Display: Toggle respective drum square and level meter
			//trigger drum sound
			break;
		case KEY_M:
			//Display: Show S to indicate mode change
			app->setState(1);	//change state to SequencerMode
			break;
		case KEY_COMMA:
			//Display: Show new master volume
			//decrease master volume
			break;
		case KEY_DOT:
			//Display: Show new master volume
			//increase master volume
			break;
		case KEY_V:
			app->setState(3);	//change state to SetDrumVolumeMode
			break;
	}
}


SequencerMode::SequencerMode() {
	label = SEQUENCER_MODE;
	currentdrum = KICK_DRUM;	//default drum A
	currentpage = 1;	//default page 1 (beats 1-8)
	playing = 0;	//sequencer stopped by default
	//Display: Show kick drum page 1 sequence
}

void SequencerMode::interpretKeyPress(ApplicationCallback* app, int key) {
	switch (key) {
		case KEY_A:
			//Display: Toggle corresponding DP
			//change currentdrum to drum A
			currentdrum = KICK_DRUM;
			//display currentpage for drum A
			break;
		case KEY_S:
			//Display: Toggle corresponding DP
			//change currentdrum to drum S
			currentdrum = SNARE_DRUM;
			//display currentpage for drum S
			break;
		case KEY_D:
			//Display: Toggle corresponding DP
			//change currentdrum to drum D
			//display currentpage for drum D
			break;
		case KEY_F:
			//Display: Toggle corresponding DP
			//change currentdrum to drum F
			//display currentpage for drum F
			break;
		case KEY_J:
			//Display: Toggle corresponding DP
			//change currentdrum to drum J
			//display currentpage for drum J
			break;
		case KEY_K:
			//Display: Toggle corresponding DP
			//change currentdrum to drum K
			//display currentpage for drum K
			break;
		case KEY_L:
			//Display: Toggle corresponding DP
			//change currentdrum to drum L
			//display currentpage for drum L
			break;
		case KEY_SEMICOLON:
			//Display: Toggle corresponding DP
			//change currentdrum to drum ;
			//display currentpage for drum ;
			break;
		case KEY_1:
			//Display: Toggle upper squre on beat
			if (currentpage == 1) {
				//Insert currentdrum into beat 1
			} else if (currentpage == 2) {
				//insert currentdrum into beat 9
			}
			break;
		case KEY_2:
			//Display: Toggle upper squre on beat
			if (currentpage == 1) {
				//Insert currentdrum into beat 2
			} else if (currentpage == 2) {
				//insert currentdrum into beat 10
			}
			break;
		case KEY_3:
			//Display: Toggle upper squre on beat
			if (currentpage == 1) {
				//Insert currentdrum into beat 3
			} else if (currentpage == 2) {
				//insert currentdrum into beat 11
			}
			break;
		case KEY_4:
			//Display: Toggle upper squre on beat
			if (currentpage == 1) {
				//Insert currentdrum into beat 4
			} else if (currentpage == 2) {
				//insert currentdrum into beat 12
			}
			break;
		case KEY_5:
			//Display: Toggle upper squre on beat
			if (currentpage == 1) {
				//Insert currentdrum into beat 5
			} else if (currentpage == 2) {
				//insert currentdrum into beat 13
			}
			break;
		case KEY_6:
			//Display: Toggle upper squre on beat
			if (currentpage == 1) {
				//Insert currentdrum into beat 6
			} else if (currentpage == 2) {
				//insert currentdrum into beat 14
			}
			break;
		case KEY_7:
			//Display: Toggle upper squre on beat
			if (currentpage == 1) {
				//Insert currentdrum into beat 7
			} else if (currentpage == 2) {
				//insert currentdrum into beat 15
			}
			break;
		case KEY_8:
			//Display: Toggle upper squre on beat
			if (currentpage == 1) {
				//Insert currentdrum into beat 8
			} else if (currentpage == 2) {
				//insert currentdrum into beat 16
			}
			break;
		case KEY_TAB:
			if (currentpage == 1) {
				currentpage = 2;	//switch to 2nd page (beats 9-16)
				//display beats 9-16 for currentdrum
			} else if (currentpage == 2) {
				currentpage = 1;	//switch to 1st page (beats 1-8)
				//display beats 1-8 for currentdrum
			}
			break;
		case KEY_SPACE:
			// Toggle play/pause sequence display
			playing = !playing;	//Toggle play/pause
			break;
		case KEY_M:
			//Display: switch to performance display mode
			//stop sequencer before switching to PerformanceMode
			playing = 0;
			app->setState(0);	//change state to PerformanceMode
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
			app->setState(2);	//change state to SetTempoMode
			break;
		case KEY_V:
			app->setState(3);	//change state to SetDrumVolumeMode
			break;
	}
}


SetTempoMode::SetTempoMode() {
	label = SET_TEMPO_MODE;
}

void SetTempoMode::interpretKeyPress(ApplicationCallback* app, int key) {
	switch (key) {
		case KEY_DOT:
			//increase tempo (should tempo variable be a member of SetTempoMode or Application??)
			break;
		case KEY_COMMA:
			//decrease tempo
			break;
		case KEY_T:
			app->setState(1);	//change state to SequencerMode
			break;
		case KEY_ESC:
			app->setState(1);	//change state to SequencerMode
			break;
	}
}


SetDrumVolumeMode::SetDrumVolumeMode() {
	label = SET_DRUM_VOLUME_MODE;
	drumselected = KICK_DRUM;	//default drum A
	previousstate = PERFORMANCE_MODE;	//default previous state
}

void SetDrumVolumeMode::interpretKeyPress(ApplicationCallback *app, int key) {
	switch (key) {
		case KEY_DOT:
			//increaseDrumVolume(drumselected);	//increase selected drum volume in some way
			//trigger drumselected?
			break;
		case KEY_COMMA:
			//decreaseDrumVolume(drumselected);
			//trigger drumselected?
			break;
		case KEY_A:
			drumselected = KICK_DRUM;	//set drumselected to drum A
			break;
		case KEY_S:
			//set drumselected to drum S
			break;
		case KEY_D:
			//set drumselected to drum D
			break;
		case KEY_F:
			//set drumselected to drum F
			break;
		case KEY_J:
			//set drumselected to drum J
			break;
		case KEY_K:
			//set drumselected to drum K
			break;
		case KEY_L:
			//set drumselected to drum L
			break;
		case KEY_SEMICOLON:
			//set drumselected to drum SEMICOLON
			break;
		case KEY_V:
			//change state back to previous state
			if (previousstate == PERFORMANCE_MODE) {
				app->setState(0);	//change state to PerformanceMode
			} else if (previousstate == SEQUENCER_MODE) {
				app->setState(1);	//change state to SequencerMode
			}
			break;
		case KEY_ESC:
			//change state back to previous state
			if (previousstate == PERFORMANCE_MODE) {
				app->setState(0);	//change state to PerformanceMode
			} else if (previousstate == SEQUENCER_MODE) {
				app->setState(1);	//change state to SequencerMode
			}
			break;
	}
}


//Application

Application::Application() {
	currentstate = &performancemode;

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

	while(1) {
		if (kbdThread.kbdIn.keyPressedFlag == 1) {
			currentstate->interpretKeyPress(this, kbdThread.kbdIn.keyPressed);
			kbdThread.kbdIn.keyPressedFlag = 0;
		}
	}
}

void Application::setState(int newstate) {
	switch (newstate) {
		case 0:
			currentstate = &performancemode;
			//switch display to performance mode
			break;
		case 1:
			currentstate = &sequencermode;
			sequencermode.currentpage = 1;	//switch to default page
			sequencermode.currentdrum = KICK_DRUM;	//switch to default drum A
			//switch display to sequencer mode
			break;
		case 2:
			currentstate = &settempomode;
			break;
		case 3:
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
