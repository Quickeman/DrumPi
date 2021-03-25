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
- USB audio interface (required)

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

### Startup
To start the DrumPi, enter:
```
./DrumPi
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
- Audio interface flexibility 
