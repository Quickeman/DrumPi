<h1 align="center">DrumPi</h1>
<p align="center">
  <a href="https://github.com/Quickeman/DrumPi">
    <img src="/images/drumpi_logo.png" alt="Logo" height="300">
  </a>

  <p align="center">A drum machine made for the Raspberry Pi</p>  
</p>

## Contents
<ul>
  <li><a href="#About">About</a>
    <ul>
      <li><a href="#Functionality">Functionality</a>
      <li><a href="#Hardware">Hardware</a>
    </ul>
  <li><a href="#Quick-Start-Guide">Quick Start Guide</a>
    <ul>
      <li><a href="#Setup">Setup</a>
      <li><a href="#Installation">Installation</a>
      <li><a href="#Startup">Startup</a>
      <li><a href="#Running-Tests">Running Tests</a>
    </ul>
  <li><a href="#Usage">Usage</a>
  <li><a href="#Stretch-Goals">Stretch Goals</a>
</ul>

## About
DrumPi is a small, affordable, open-source drum machine, giving you all the percussive power you need in a pocket-sized package.

### Functionality
- 'Live Performance' and 'Sequencer' modes
- Visual feedback provided via an 8-digit 7-segment display
- Standard USB keyboard control interface

### Hardware
- Raspberry Pi (designed on RPI 4B)
- ZeroSeg 8-digit 7-segment display
- Standard USB keyboard
- USB audio interface

## Quick Start Guide
### Installation
#### Prerequisites
Before downloading and installing DrumPi's software on your Raspberry Pi, perform the following steps:    
First, run the following in a terminal:
```
sudo apt install git cmake libboost-test-dev libjack-jackd2-dev
sudo adduser $(whoami) input
sudo adduser $(whoami) audio
sudo adduser $(whoami) spi
```
Reboot system before continuing.    
To enable the SPI interface, run the following in a terminal:
```
sudo raspi-config
```
Navigate to Interface Options -> SPI.   
Enable SPI interface.   

#### DrumPi
To download and build the DrumPi program, run the following in a terminal:
```
git clone https://github.com/Quickeman/DrumPi.git
cd DrumPi
./install
```

### Startup
To start the DrumPi, enter:
```
./DrumPi
```
in a terminal from the DrumPi directory.

### Running Tests
To run the suite of unit tests, enter:
```
./run_tests
```
in a terminal from the DrumPi directory

## Usage
When turned on, the DrumPi defaults to performance mode.

Global Actions:
```
KEY		ACTION
M		Switch between performance and sequencer mode
ESC		Exit program
.		Increase master volume
,		Decrease master volume
V		Switch to "Set Drum Volume" Mode
```
Performance Mode:  
```
KEY		ACTION
A		Play drum 1
S		Play drum 2
D		Play drum 3
F		Play drum 4
J		Play drum 5
K		Play drum 6
L		Play drum 7
;		Play drum 8
```
Sequencer Mode:
```
When entering sequencer mode, drum 1 and page 1 are displayed by default.

KEY		ACTION
A,S,D,F,J,K,L,;	Select drum
1-8		Toggle whether drum sound plays for that beat
		When page 1 is displayed, will toggle beats 1-8
		When page 2 is displayed, will toggle beats 9-16
TAB		Switch between page 1 and 2
SPACE		Start/stop sequence
T		Switch to "Set Tempo" mode		
```
Set Drum Volume Sub-Mode:
```
Can enter this mode from both Performance mode and Sequencer mode.

KEY		ACTION
.		Increase volume of selected drum
,		Decrease volume of selected drum
A		Switch selected drum to drum 1
S		Switch selected drum to drum 2
D		Switch selected drum to drum 3
F		Switch selected drum to drum 4
J		Switch selected drum to drum 5
K		Switch selected drum to drum 6
L		Switch selected drum to drum 7
;		Switch selected drum to drum 8
V		Exit "Set Drum Volume" Mode
BACKSPACE	Exit "Set Drum Volume" Mode
```
Set Tempo Sub-Mode:
``
.		Increase tempo
,		decrease tempo
T		Exit "Set Tempo" sub-mode, return to Sequencer mode
BACKSPACE	Exit "Set Tempo" sub-mode, return to Sequencer mode
```

## Stretch Goals
- External clocking
- Customisation of drum sounds by user
- Ability for real-time DSP using Pd patches
