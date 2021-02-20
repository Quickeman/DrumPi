// File: clock.cpp

#include "clock.hpp"

using namespace drumpi;
using namespace clock;

Timer::Timer() {}

void Timer::setTime(int ms) {}

int Timer::getTime() {return 0;}

void Timer::start() {};

void Timer::trigger() {}

void Timer::timerEvent() {};


Clock::Clock() {}

void Clock::setRate(int ms) {}

int Clock::getRate() {return 0;}

void Clock::start() {}

void Clock::tick() {}

void Clock::timerEvent() {}


Metronome::Metronome() {}

void Metronome::setRateBPM(int bpm) {}

int Metronome::getRateBPM() {return 0;}