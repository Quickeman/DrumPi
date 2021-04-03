// File: clock.cpp

#include "clock.hpp"

using namespace drumpi;
using namespace clock;

Timer::Timer() {
    setTime(1000);
    active = false;
}

Timer::~Timer() {
    stop();
}

void Timer::setTime(int ms) {
    time = ms;
}

int Timer::getTime() {
    return time;
}

void Timer::start() {
    CppTimer::start(long(time * 1000000), ONESHOT);
    active = true;
}

void Timer::stop() {
    CppTimer::stop();
    active = false;
}

bool Timer::isActive() {
    return active;
}

void Timer::timerEvent() {
    trigger();
    active = false;
};


Clock::Clock() {
    setRate(1000);
    rateChangeFlag = false;
    active = false;
}

Clock::~Clock() {
    stop();
}

void Clock::setRate(int ms) {
    rate = ms;
    rateChangeFlag = true;
}

int Clock::getRate() {
    return rate;
}

void Clock::start() {
    CppTimer::start(long(rate*1000000));
    timerEvent();
    active = true;
}

void Clock::stop() {
    CppTimer::stop();
    active = false;
}

bool Clock::isActive() {
    return active;
}

void Clock::timerEvent() {
    if (rateChangeFlag) {
        rateChangeFlag = false;
        stop();
        start();
        return;
    }
    tick();
}


Metronome::Metronome() {
    setRateBPM(120);
    rateChangeFlag = false;
}

void Metronome::setRateBPM(int bpm) {
    this->bpm = bpm;
    setRate(bpmToMs(this->bpm));
}

int Metronome::getRateBPM() {
    return bpm;
}
