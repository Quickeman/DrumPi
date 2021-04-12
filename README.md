<h1 align="center">DrumPi</h1>
<p align="center">
  <a href="https://github.com/Quickeman/DrumPi">
    <img src="/images/drumpi_logo.png" alt="Logo" height="300">
  </a>

  <p align="center">A drum machine made for the Raspberry Pi.</p>  
</p>

## Contents
<ul>
  <li><a href="#About">About</a>
    <ul>
      <li><a href="#Functionality">Functionality</a>
      <li><a href="#Hardware">Hardware</a>
    </ul>
  <li><a href="#Quick Start Guide">Quick-start guide</a>
    <ul>
      <li><a href="#Setup">Setup</a>
      <li><a href="#Installation">Installation</a>
      <li><a href="#Startup">Startup</a>
      <li><a href="#Running Tests">Running Tests</a>
    </ul>
  <li><a href="#Usage">Usage</a>
  <li><a href="#Stretch Goals">Stretch Goals</a>
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

## Quick-start guide
### Setup
Before downloading and installing DrumPi's software on your Raspberry Pi, perform the following steps:    
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

### Installation
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
Performance Mode:  
```
KEY		ACTION
A		Tom 1
S		Tom 2
D		Snare
F		Kick
J		Clap
K		Hi-hat (closed)
L		hi-hat (open)
;		Cymbal
.		Increase master volume
,		Decrease master volume
V		Switch to "Set Drum Volume" Mode
BACKSPACE	Exit program
```
Set Drum Volume Mode:
```
KEY		ACTION
.		Increase volume of selected drum
,		Decrease volume of selected drum
A		Switch selected drum to Tom 1
S		Switch selected drum to Tom 2
D		Switch selected drum to Snare
F		Switch selected drum to Kick
J		Switch selected drum to Clap
K		Switch selected drum to Hi-hat (closed)
L		Switch selected drum to Hi-hat (open)
;		Switch selected drum to Cymbal
V		Exit "Set Drum Volume" Mode
ESC		Exit "Set Drum Volume" Mode
BACKSPACE	Exit program
```

## Stretch Goals
- External clocking
- Customisation of drum sounds by user
- Ability for real-time DSP using Pd patches
