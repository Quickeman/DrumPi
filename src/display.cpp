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

void Display::showVal(unsigned int value) {
    // Clear digits
    clear(false);

    // Separate value into individual digits
    // 3 digits:
    if(value > 99) setThreeDigits(value);
    // 2 digits:
    else if ((value > 9) && (value <= 99)) setTwoDigits(value);
    // 1 digit:
    else if (value <= 9) setOneDigit(value);

    // Flush display
    flush();
}

void Display::setThreeDigits(unsigned int value) {
    clear(false);

    unsigned char digitOne, digitTwo, digitThree;
    digitOne = decHexVals[value % 10];
    digitTwo = decHexVals[(value/10) % 10];
    digitThree = decHexVals[(value/100) % 10];

    setDigit(5, digitOne, false);
    setDigit(6, digitTwo, false);
    setDigit(7, digitThree, false);
    flush();
}

void Display::setTwoDigits(unsigned int value) {
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

void Display::toggleDPFlash() {
    // If dp is off, turn on
    if (!dpToggle) {
        for (unsigned int digit = 0; digit < numDigits; digit ++) {
            unsigned char toggled = getDigit(digit) + 0x80;
            setDigit(digit, toggled, false);
        }
        dpToggle = true;
    }
    else {
        for (unsigned int digit = 0; digit < numDigits; digit ++) {
            unsigned char toggled = getDigit(digit) - 0x80;
            setDigit(digit, toggled, false);
        }
        dpToggle = false;
    }
    flush();
}

void Display::showLevel(float level) {
    // Clear display
    clear(false);
    float magLevel = fabs(level);
    unsigned int maxDigit = magLevel * numDigits;

    // Apply level to digits
    for(unsigned int digit = 0; digit <= maxDigit; digit ++)
        setDigit(numDigits - digit, 0x8, false);

    flush();
}

