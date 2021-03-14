#define MAX7219_REG_NOOP 0x0
#define MAX7219_REG_DIGIT0 0x1
#define MAX7219_REG_DIGIT1 0x2
#define MAX7219_REG_DIGIT2 0x3
#define MAX7219_REG_DIGIT3 0x4
#define MAX7219_REG_DIGIT4 0x5
#define MAX7219_REG_DIGIT5 0x6
#define MAX7219_REG_DIGIT6 0x7
#define MAX7219_REG_DIGIT7 0x8
#define MAX7219_REG_DECODEMODE 0x09
#define MAX7219_REG_INTENSITY 0xA
#define MAX7219_REG_SCANLIMIT 0xB
#define MAX7219_REG_SHUTDOWN 0xC
#define MAX7219_REG_DISPLAYTEST 0xF

#include "display.hpp"

using namespace drumpi;
using namespace display;

Max7219::Max7219(unsigned char decodeMode,
                unsigned char intensity,
                unsigned char scanLimit,
                unsigned char shutdown,
                unsigned char displayTest,
                unsigned int numDigits):
    decodeMode(decodeMode),
    intensity(intensity),
    scanLimit(scanLimit),
    shutdown(shutdown),
    displayTest(displayTest),
    numDigits(numDigits)
{
    // Allocate digit buffer and init to 0
    digitBuffer = new unsigned char[numDigits];
    clear(true);

    // Init SPI
    wiringPiSPISetup(0, 32000000);

    // Set command regs
    command(MAX7219_REG_DECODEMODE, decodeMode);
    command(MAX7219_REG_INTENSITY, intensity);
    command(MAX7219_REG_SCANLIMIT, scanLimit);
    command(MAX7219_REG_SHUTDOWN, shutdown);
    command(MAX7219_REG_DISPLAYTEST, displayTest);
}

Max7219::~Max7219() {
    delete digitBuffer;
    clear(true);
}

// Getters //

unsigned char Max7219::getDigit(unsigned char digit) {
    return digitBuffer[digit];
}

unsigned char Max7219::getDecodeMode(){
    return decodeMode;
}
unsigned char Max7219::getIntensity(){
    return intensity;
}
unsigned char Max7219::getScanLimit(){
    return scanLimit;
}
unsigned char Max7219::getShutdown(){
    return shutdown;
}
unsigned char Max7219::getDisplayTest(){
    return displayTest;
}
unsigned int Max7219::getNumDigits() {
    return numDigits;
}

// Setters //

void Max7219::setDigit(unsigned char digit, unsigned char value, bool redraw) {
    digitBuffer[digit] = value;
    if(redraw) flush();
}

void Max7219::setDecodeMode(unsigned char value){
    decodeMode = value;
    command(MAX7219_REG_DECODEMODE, value);
}
void Max7219::setIntensity(unsigned char value){
    intensity = value;
    command(MAX7219_REG_INTENSITY, value);
}
void Max7219::setScanLimit(unsigned char value){
    scanLimit = value;
    command(MAX7219_REG_SCANLIMIT, value);
}
void Max7219::setShutdown(unsigned char value){
    shutdown = value;
    command(MAX7219_REG_SHUTDOWN, value);
}
void Max7219::setDisplayTest(unsigned char value){
    displayTest = value;
    command(MAX7219_REG_DISPLAYTEST, value);
}

// Actions //

void Max7219::write(unsigned char* data, unsigned int len) {
    wiringPiSPIDataRW(0, data, len);
}

void Max7219::command(unsigned char reg, unsigned char data) {
    unsigned char tx[2] = {reg, data};
    write(tx, 2);
}

void Max7219::flush() {
    unsigned char tx[2];
    for (unsigned char digit = 0; digit < numDigits; digit ++) {
        tx[0] = digit + 1; // digits addresses are 1-8
        tx[1] = digitBuffer[digit];
        write(tx,2);
    }
}

void Max7219::clear(bool redraw) {
    for (unsigned int digit = 0; digit < numDigits; digit ++)
        digitBuffer[digit] = 0x0;
    if(redraw) flush();
}

// Display class

Display::Display() {
    dpToggle = false;
}

Display::~Display() {
}

void Display::setVal(unsigned int value, bool redraw) {
    clear(false);
    // Separate value into individual digits
    // 3 digits:
    if(value > 99) setThreeDigit(value);
    // 2 digits:
    else if ((value > 9) && (value <= 99)) setTwoDigit(value);
    // 1 digit:
    else if (value <= 9) setOneDigit(value);
    if (redraw) flush();
}

void Display::setThreeDigit(unsigned int value) {
    unsigned char digitOne, digitTwo, digitThree;
    digitOne = decHexVals[value % 10];
    digitTwo = decHexVals[(value/10) % 10];
    digitThree = decHexVals[(value/100) % 10];

    setDigit(5, digitOne, false);
    setDigit(6, digitTwo, false);
    setDigit(7, digitThree, false);
    flush();
}

void Display::setTwoDigit(unsigned int value) {
    unsigned char digitOne, digitTwo;
    digitOne = decHexVals[value % 10];
    digitTwo = decHexVals[(value/10) % 10];

    setDigit(6, digitOne, false);
    setDigit(7, digitTwo, false);
}

void Display::setOneDigit(unsigned int value) {
    unsigned char digitOne;
    digitOne = decHexVals[value % 10];

    setDigit(7, digitOne, false);
}

void Display::toggleDPFlash(bool redraw) {
    // If dp is off, turn on
    if (!dpToggle) {
        for (unsigned int digit = 0; digit < getNumDigits(); digit ++) {
            unsigned char toggled = getDigit(digit) + dpAddr;
            setDigit(digit, toggled, false);
        }
        dpToggle = true;
    }
    else {
        for (unsigned int digit = 0; digit < getNumDigits(); digit ++) {
            unsigned char toggled = getDigit(digit) - dpAddr;
            setDigit(digit, toggled, false);
        }
        dpToggle = false;
    }
    if(redraw) flush();
}

void Display::setLevel(float level, bool redraw) {
    clear(false);
    float magLevel = fabs(level);
    unsigned int maxDigit = magLevel * getNumDigits();

    for(unsigned int digit = 0; digit <= maxDigit; digit ++)
        setDigit(getNumDigits() - digit -1, 0x8, false);

    if(redraw) flush();
}

void Display::setActiveDrums(std::vector<bool> activeDrums, unsigned int page) {
    unsigned int seqIndex;
    for(unsigned int digit = 0; digit <= getNumDigits(); digit ++) {
        seqIndex = (page*getNumDigits()) + digit;
        if(activeDrums[seqIndex])
            setDigit((getNumDigits()-1) - digit, upperSqAddr, false);
    }
}

void Display::setStopSeq(std::vector<bool> activeDrums, unsigned int page, unsigned int currentDrum, bool redraw) {
    clear(false);
    setActiveDrums(activeDrums, page);
    setDigit(getNumDigits() - currentDrum, getDigit(getNumDigits()-currentDrum) + dpAddr, false);
    if(redraw) flush();
}

void Display::setPlaybackSeq(std::vector<bool> activeDrums, unsigned int stepNum, bool redraw) {
    clear(false);
    unsigned int page = stepNum > getNumDigits();
    setActiveDrums(activeDrums, page);
    if(stepNum <= getNumDigits()) {
        unsigned char addr = getNumDigits() -stepNum;
        setDigit(addr, getDigit(addr) + bottomAddr, false);
    }
    else {
        unsigned char addr = getNumDigits() - (stepNum%8);
        setDigit(addr, getDigit(addr) + dpAddr, false);
    }
    flush();
}
