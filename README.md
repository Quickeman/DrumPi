# DrumPi
A drum machine made using a Raspberry Pi.

## About
DrumPi is a small, affordable, open-source drum machine, giving you all the percussive power you need in a pocket-sized package.

### Functionality
- 'Live Performance' and 'Sequencer' modes
- Visual feedback provided via an 8-digit 7-segment display
- Standard USB keyboard control interface

### Components
- Raspberry Pi (designed on RPI 4B)
- ZeroSeg 8-digit 7-segment display
- Standard USB keyboard
- USB audio interface

## Quick-start guide
### Installation
To download and install DrumPi's software on your Raspberry Pi, perform the following steps:    
First, run the following in a terminal:
```
sudo apt install git cmake libboost-test-dev libjack-jackd2-dev
sudo adduser <username> input
sudo adduser <username> audio
sudo adduser <username> spi
```
Reboot system before continuing.    
To enable the SPI interface, run the following in a terminal:
```
sudo raspi-config
```
Navigate to Interface Options -> SPI.   
Enable SPI interface.   
Finally, to download and build the DrumPi program, run the following in a terminal:
```
git clone https://github.com/Quickeman/DrumPi.git
cd DrumPi
cmake .
make
```

## Usage
Performance Mode:  
```
KEY	Action
A	Tom 1
S	Tom 2
D	Snare
F	Kick
J	Clap
K	Hi-hat (closed)
L	hi-hat (open)
;	Cymbal
.	Increase master volume
,	Decrease master volume
V	Switch to "Set Drum Volume" Mode
```
Set Drum Volume Mode
```
.	Increase volume of selected drum
,	Decrease volume of selected drum
A	Switch selected drum to Tom 1
S	Switch selected drum to Tom 2
D	Switch selected drum to Snare
F	Switch selected drum to Kick
J	Switch selected drum to Clap
K	Switch selected drum to Hi-hat (closed)
L	Switch selected drum to Hi-hat (open)
;	Switch selected drum to Cymbal
V	Exit "Set Drum Volume" Mode
```

### Startup
To start the DrumPi, enter:
```
bash DrumPi.sh
```
in a terminal from the DrumPi directory.

### Running Tests
To run a suite of unit tests, enter:
```
make test
```
in a terminal from the DrumPi directory

## Stretch Goals
- External clocking
- Customisation of drum sounds by user
- Ability for real-time DSP using Pd patches
