#define MAX7219_REG_NOOP = 0x0
#define MAX7219_REG_DIGIT0 = 0x1
#define MAX7219_REG_DIGIT1 = 0x2
#define MAX7219_REG_DIGIT2 = 0x3
#define MAX7219_REG_DIGIT3 = 0x4
#define MAX7219_REG_DIGIT4 = 0x5
#define MAX7219_REG_DIGIT5 = 0x6
#define MAX7219_REG_DIGIT6 = 0x7
#define MAX7219_REG_DIGIT7 = 0x8
#define MAX7219_REG_DECODEMODE = 0x9
#define MAX7219_REG_INTENSITY = 0xA
#define MAX7219_REG_SCANLIMIT = 0xB
#define MAX7219_REG_SHUTDOWN = 0xC0
#define MAX7219_REG_DISPLAYTEST = 0xF

#include <stdint.h>

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
        void getByte(uint8_t digit);
        void getDecodeMode();
        void getIntensity();
        void getScanLimit();
        void getShutdown();
        void getDisplayTest();

        // Actions
        void flush();
        void clear();
        void command(uint8_t reg, uint8_t data);
};
