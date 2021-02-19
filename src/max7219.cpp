#define MAX7219_REG_NOOP 0x0
#define MAX7219_REG_DIGIT0 0x1
#define MAX7219_REG_DIGIT1 0x2
#define MAX7219_REG_DIGIT2 0x3
#define MAX7219_REG_DIGIT3 0x4
#define MAX7219_REG_DIGIT4 0x5
#define MAX7219_REG_DIGIT5 0x6
#define MAX7219_REG_DIGIT6 0x7
#define MAX7219_REG_DIGIT7 0x8
#define MAX7219_REG_DECODEMODE 0x9
#define MAX7219_REG_INTENSITY 0xA
#define MAX7219_REG_SCANLIMIT 0xB
#define MAX7219_REG_SHUTDOWN 0xC0
#define MAX7219_REG_DISPLAYTEST 0xF

#include "max7219.hpp"
extern "C" {
#include <wiringPiSPI.h>
}

Max7219::Max7219(unsigned char decodeMode,
                unsigned char intensity,
                unsigned char scanLimit,
                unsigned char shutdown,
                unsigned char displayTest):
    decodeMode(decodeMode),
    intensity(intensity),
    scanLimit(scanLimit),
    shutdown(shutdown),
    displayTest(displayTest)
{
    wiringPiSPISetup(0, 500000);
    command(MAX7219_REG_DECODEMODE, decodeMode);
    command(MAX7219_REG_INTENSITY, decodeMode);
    command(MAX7219_REG_SCANLIMIT, decodeMode);
    command(MAX7219_REG_SHUTDOWN, decodeMode);
    command(MAX7219_REG_DISPLAYTEST, decodeMode);
}

Max7219::~Max7219() {
}

// Getters //
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

void Max7219::write(unsigned char* data, unsigned int len) {
    wiringPiSPIDataRW(0, data, len);
}

void Max7219::command(unsigned char reg, unsigned char data) {
    unsigned char tx[2] = {reg, data};
    write(tx, 2);
}
