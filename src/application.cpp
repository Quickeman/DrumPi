//application.cpp

#include "application.hpp"

using namespace drumpi;


//States

PerformanceMode::PerformanceMode() {
	label = "performancemode";
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
			app->setState(1);	//change state to SequencerMode
			break;
		case KEY_COMMA:
			//decrease master volume
			break;
		case KEY_DOT:
			//increase master volume
			break;
		case KEY_V:
			app->setState(3);	//change state to SetDrumVolumeMode
			break;
	}
}


SequencerMode::SequencerMode() {
	label = "sequencermode";
	currentdrum = KICK_DRUM;	//default drum A
	currentpage = 1;	//default page 1 (beats 1-8)
	playing = 0;	//sequencer stopped by default
}

void SequencerMode::interpretKeyPress(ApplicationCallback* app, int key) {
	switch (key) {
		case KEY_A:
			//change currentdrum to drum A
			//display currentpage for drum A
			break;
		case KEY_S:
			//change currentdrum to drum S
			//display currentpage for drum S
			break;
		case KEY_D:
			//change currentdrum to drum D
			//display currentpage for drum D
			break;
		case KEY_F:
			//change currentdrum to drum F
			//display currentpage for drum F
			break;
		case KEY_J:
			//change currentdrum to drum J
			//display currentpage for drum J
			break;
		case KEY_K:
			//change currentdrum to drum K
			//display currentpage for drum K
			break;
		case KEY_L:
			//change currentdrum to drum L
			//display currentpage for drum L
			break;
		case KEY_SEMICOLON:
			//change currentdrum to drum ;
			//display currentpage for drum ;
			break;
		case KEY_1:
			if (currentpage == 1) {
				//Insert currentdrum into beat 1
			} else if (currentpage == 2) {
				//insert currentdrum into beat 9
			}
			break;
		case KEY_2:
			if (currentpage == 1) {
				//Insert currentdrum into beat 2
			} else if (currentpage == 2) {
				//insert currentdrum into beat 10
			}
			break;
		case KEY_3:
			if (currentpage == 1) {
				//Insert currentdrum into beat 3
			} else if (currentpage == 2) {
				//insert currentdrum into beat 11
			}
			break;
		case KEY_4:
			if (currentpage == 1) {
				//Insert currentdrum into beat 4
			} else if (currentpage == 2) {
				//insert currentdrum into beat 12
			}
			break;
		case KEY_5:
			if (currentpage == 1) {
				//Insert currentdrum into beat 5
			} else if (currentpage == 2) {
				//insert currentdrum into beat 13
			}
			break;
		case KEY_6:
			if (currentpage == 1) {
				//Insert currentdrum into beat 6
			} else if (currentpage == 2) {
				//insert currentdrum into beat 14
			}
			break;
		case KEY_7:
			if (currentpage == 1) {
				//Insert currentdrum into beat 7
			} else if (currentpage == 2) {
				//insert currentdrum into beat 15
			}
			break;
		case KEY_8:
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
			if (playing == 0) {
				playing = 1;
				//start sequencer
			} else if (playing == 1) {
				playing = 0;
				//stop sequencer
			}
			break;
		case KEY_M:
			//stop sequencer before switching to PerformanceMode
			playing = 0;
			app->setState(0);	//change state to PerformanceMode
			break;
		case KEY_COMMA:
			//decrease master volume
			break;
		case KEY_DOT:
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
	label = "settempomode";
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
	label = "settempomode";
	drumselected = KICK_DRUM;	//default drum A
	previousstate = "performancemode";	//default previous state
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
			if (previousstate == "performancemode") {
				app->setState(0);	//change state to PerformanceMode
			} else if (previousstate == "sequencermode") {
				app->setState(1);	//change state to SequencerMode
			}
			break;
		case KEY_ESC:
			//change state back to previous state
			if (previousstate == "performancemode") {
				app->setState(0);	//change state to PerformanceMode
			} else if (previousstate == "sequencermode") {
				app->setState(1);	//change state to SequencerMode
			}
			break;
	}
}


//Application

Application::Application() {
	currentstate = &performancemode;
}

void Application::run() {
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
				setdrumvolumemode.previousstate = "sequencermode";
				currentstate = &setdrumvolumemode;
			} else if (currentstate == &performancemode) {
				setdrumvolumemode.previousstate = "performancemode";
				currentstate = &setdrumvolumemode;
			}
			break;
	}
}
