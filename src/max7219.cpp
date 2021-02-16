#include "max7219.hpp"
#include <wiringPiSPI.h>

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
    int init = wiringPiSPISetup(0, 500000);
}

Max7219::~Max7219() {
}

void Max7219::write(unsigned char* data, unsigned int len) {
    wiringPiSPIDataRW(0, data, len);
}
