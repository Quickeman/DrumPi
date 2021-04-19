<h1 align="center">DrumPi</h1>
<p align="center">
  <a href="https://github.com/Quickeman/DrumPi">
    <img src="/images/drumpi_logo.png" alt="Logo" height="300">
  </a>

  <p align="center">A drum machine made for the Raspberry Pi</p>  
</p>

<p align="center">
  <a href="https://www.facebook.com/DrumPiProject/">Facebook</a>
  <span> | </span>
  <a href="https://www.instagram.com/drumpiproject/">Instagram</a>
</p>

<p align="center">
    <a href="https://github.com/Quickeman/DrumPi/graphs/contributors" alt="Contributors">
        <img src="https://img.shields.io/github/contributors/Quickeman/DrumPi.svg" /></a>
    <a href="https://github.com/Quickeman/DrumPi/stargazers" alt="Stars">
        <img src="https://img.shields.io/github/stars/Quickeman/DrumPi.svg" /></a>
    <a href="https://github.com/Quickeman/DrumPi/issues" alt="Issues">
        <img src="https://img.shields.io/github/issues/Quickeman/DrumPi.svg" /></a>
    <a href="https://github.com/Quickeman/DrumPi/blob/main/LICENSE" alt="License">
        <img src="https://img.shields.io/github/license/Quickeman/DrumPi.svg" /></a>
    <a href="https://github.com/Quickeman/DrumPi/releases" alt="Tag">
        <img src="https://img.shields.io/github/v/release/Quickeman/DrumPi.svg?color=blue&include_prereleases" alt="build status"></a>
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
      <li><a href="#Installation">Installation</a>
      <li><a href="#Startup">Startup</a>
      <li><a href="#Running-Tests">Running Tests</a>
    </ul>
  <li><a href="#Usage">Usage</a>
  <li><a href="#Documentation">Documentation</a>
  <li><a href="#Stretch-Goals">Stretch Goals</a>
</ul>

## About
DrumPi is a small, affordable, open-source drum machine, giving you all the percussive power you need in a pocket-sized package.

[Click here to see the launch video!](https://www.youtube.com/watch?v=tMC3NiNRklU)

### Functionality
- 'Live Performance' and 'Sequencer' modes
- Visual feedback provided via an 8-digit 7-segment display
- Standard USB keyboard control interface

### Hardware
- [Raspberry Pi](https://thepihut.com/products/raspberry-pi-4-model-b)
- [ZeroSeg](https://thepihut.com/products/zeroseg) 8-digit 7-segment display
- Standard USB computer keyboard, including 60% keyboards
- USB audio interface, such as [this](https://thepihut.com/products/usb-audio-adapter-works-with-raspberry-pi)

## Quick Start Guide
### Installation
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

To download and build the DrumPi program, run the following in a terminal:
```
git clone https://github.com/Quickeman/DrumPi.git
cd DrumPi
./install
```

For more details, see the [Installation Guide](https://github.com/Quickeman/DrumPi/wiki/Installation-Guide).

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
in a terminal from the DrumPi directory.

## Usage

For instructions on how to use the DrumPi application, see the [User Manual](https://github.com/Quickeman/DrumPi/wiki/User-Manual).

## Documentation

[DrumPi Documentation](https://quickeman.github.io/DrumPi/html/index.html)

## Stretch Goals
- External clocking
- Ability for real-time DSP using Pd patches
