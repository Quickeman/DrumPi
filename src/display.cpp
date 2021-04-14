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

// Max7219

// Low-level methods //

void Max7219::write(unsigned char* data, unsigned int len) {
    wiringPiSPIDataRW(0, data, len);
}

void Max7219::command(unsigned char reg, unsigned char data) {
    unsigned char tx[2] = {reg, data};
    write(tx, 2);
}

// Constructor & Destructor //

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
    digitBuffer.assign(numDigits, 0);

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
    clear(true);
}

// SETTERS //

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

// GETTERS //

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

// HIGH LEVEL METHODS //

void Max7219::flush() {
    unsigned char tx[2]; // Holds digit address and digit value
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

// End Max7219

// Display

// CONSTRUCTOR & DESTRUCTOR //

Display::Display() {
}

Display::~Display() {
}

// PRIVATE METHODS

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


void Display::setActiveDrums(std::vector<bool> activeDrums, unsigned int page) {
    unsigned int seqIndex = 0;
    for(unsigned int digit = 0; digit <= getNumDigits(); digit ++) {
        seqIndex = (page*getNumDigits()) + digit;
        if(activeDrums[seqIndex])
            setDigit((getNumDigits()-1) - digit, upperSqAddr, false);
    }
}

void Display::addLevel(float level) {
    float magLevel = fabs(level);
    unsigned int maxDigit = magLevel * getNumDigits();

    for(unsigned int digit = 0; digit <= maxDigit; digit ++) {
        unsigned char currentDigit = getNumDigits() - digit - 1;
        setDigit(currentDigit, getDigit(currentDigit) + 0x8, false);
    }

}

void Display::addPage(unsigned int page){
    if(page > 0) {
        for(int digit = 0; digit < 4; digit ++){
            setDigit(digit, getDigit(digit) + bottomAddr, false);
        }
    }
    else {
        for(int digit = 4; digit < 8; digit ++){
            setDigit(digit, getDigit(digit) + bottomAddr, false);
        }
    }
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

void Display::setDrumVolume(unsigned int value, drumID_t currentDrum, bool redraw) {
    clear(false);
    setVal(value, false);
    unsigned int currentKey = keyMapping[currentDrum];
    setDigit(getNumDigits() - currentKey-1, getDigit(getNumDigits()-currentKey-1) + dpAddr, false);
    if(redraw) flush();
}

void Display::setKeymapping(std::vector<unsigned int> _keyMapping) {
    keyMapping = _keyMapping;
}

void Display::setPlaybackSeq(std::vector<bool> activeDrums, unsigned int stepNum, bool redraw) {
    clear(false);
    unsigned int page = stepNum >= getNumDigits();
    setActiveDrums(activeDrums, page);
    unsigned char addr = getNumDigits() - (stepNum % 8) - 1; 
    setDigit(addr, getDigit(addr) + dpAddr, false);
    addPage(page);
    if (redraw) flush();
}

void Display::setStopSeq(std::vector<bool> activeDrums, unsigned int page, drumID_t currentDrum, bool redraw) {
    clear(false);
    setActiveDrums(activeDrums, page);
    unsigned int currentKey = keyMapping[currentDrum];
    setDigit(getNumDigits() - currentKey-1, getDigit(getNumDigits()-currentKey-1) + dpAddr, false);
    addPage(page);
    if(redraw) flush();
}

void Display::setPerformance(std::vector<drumID_t> activeDrums, float level, bool redraw) {
    clear(false);
    for(int i = 0; i < activeDrums.size(); i++) {
		setDigit(7 - keyMapping[activeDrums[i]], upperSqAddr, false);
	}
    addLevel(level);
    if(redraw) flush();
}

int Display::getKeymapping(int index){
    return keyMapping[index];
}
