#include <stdint.h>
#include <wiringPiSPI.h>

namespace drumpi {
namespace display {

class Max7219
{
    private:
        unsigned int numDigits;
        unsigned char* digitBuffer;
        unsigned char decodeMode,
                intensity,
                scanLimit,
                shutdown,
                displayTest;
        void write(unsigned char *data, unsigned int len);
        void command(unsigned char reg, unsigned char data);

    public:
        Max7219(unsigned char decodeMode = 0x0,
                unsigned char intensity = 0x7,
                unsigned char scanLimit = 0x7,
                unsigned char shutdown = 0x1,
                unsigned char displayTest = 0x0,
                unsigned int numDigits = 8);
        ~Max7219();

        // Setters
        void setDigit(unsigned char digit, unsigned char value, bool redraw);
        void setDecodeMode(unsigned char value);
        void setIntensity(unsigned char value);
        void setScanLimit(unsigned char value);
        void setShutdown(unsigned char value);
        void setDisplayTest(unsigned char value);

        // Getters
        unsigned char getDigit(unsigned char digit);
        unsigned char getDecodeMode();
        unsigned char getIntensity();
        unsigned char getScanLimit();
        unsigned char getShutdown();
        unsigned char getDisplayTest();

        // Actions
        void flush();
        void clear(bool redraw);
};
} // namespace display
} // namespace drumpi
