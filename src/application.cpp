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
			//trigger drum sound
			break;
		case KEY_S:
			//trigger drum sound
			break;
		case KEY_D:
			//trigger drum sound
			break;
		case KEY_F:
			//trigger drum sound
			break;
		case KEY_J:
			//trigger drum sound
			break;
		case KEY_K:
			//trigger drum sound
			break;
		case KEY_L:
			//trigger drum sound
			break;
		case KEY_SEMICOLON:
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
			break;
		case KEY_S:
			//change currentdrum to drum S
			break;
		case KEY_D:
			//change currentdrum to drum D
			break;
		case KEY_F:
			//change currentdrum to drum F
			break;
		case KEY_J:
			//change currentdrum to drum J
			break;
		case KEY_K:
			//change currentdrum to drum K
			break;
		case KEY_L:
			//change currentdrum to drum L
			break;
		case KEY_SEMICOLON:
			//change currentdrum to drum ;
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
				//display beats 9-16
			} else if (currentpage == 2) {
				currentpage = 1;	//switch to 1st page (beats 1-8)
				//display beats 1-8
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
	}
}


SetTempoMode::SetTempoMode() {
	tempo = 50;	//some default value
}

void SetTempoMode::interpretKeyPress(ApplicationCallback* app, int key) {
	//dostuff
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
			sequencermode.playing = 0;	//sequencer stopped by default
			//switch display to sequencer mode
			break;
	}
}
