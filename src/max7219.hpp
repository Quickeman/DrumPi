
#include <stdint.h>

extern "C" {
#include <wiringPiSPI.h>
}

class Max7219
{
    private:
        unsigned char* buffer;
        unsigned char decodeMode,
                intensity,
                scanLimit,
                shutdown,
                displayTest;
        void write(unsigned char* data, unsigned int len);
        void command(uint8_t reg, uint8_t data);

    public:
        Max7219(unsigned char decodeMode = 0x00,
                unsigned char intensity = 0x07,
                unsigned char scanLimit = 0x07,
                unsigned char shutdown = 0x01,
                unsigned char displayTest = 0x00);
        ~Max7219();

        // Setters
        void setByte(uint8_t digit, uint8_t value);
        void setDecodeMode(uint8_t value);
        void setIntensity(uint8_t value);
        void setScanLimit(uint8_t value);
        void setShutdown(uint8_t value);
        void setDisplayTest(uint8_t value);

        // Getters
        unsigned char getDigit(unsigned char digit);
        unsigned char getDecodeMode();
        unsigned char getIntensity();
        unsigned char getScanLimit();
        unsigned char getShutdown();
        unsigned char getDisplayTest();

        // Actions
        void flush();
        void clear();
};
