#include <stdint.h>
#include <vector>
#include <math.h>
#include <wiringPiSPI.h>

namespace drumpi {
namespace display {

class Max7219
{
    private:
        unsigned char* digitBuffer;
        unsigned int numDigits;
        unsigned char decodeMode,
                intensity,
                scanLimit,
                shutdown,
                displayTest;
        void write(unsigned char *data, unsigned int len);

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
        unsigned int getNumDigits();

        // Actions
        void flush();
        void clear(bool redraw);
        void command(unsigned char reg, unsigned char data);
};

class Display: public Max7219 {
    private:

        /* Vector to contain corresponding hex values
         * for decimal digit representation
         *
         * Prevents the need to toggle Code B decode
         * for every numerical display */

        const std::vector<unsigned char> decHexVals {
            0x7E, // '0'
            0x30, // '1'
            0x6D, // '2'
            0x79, // '3'
            0x33, // '4'
            0x5B, // '5'
            0x5F, // '6'
            0x70, // '7'
            0x7F, // '8'
            0x7B, // '9'
        };

        const unsigned char dpAddr = 0x80;


        // Stores state of DP (on/off)
        bool dpToggle;

        // Stores the current mode
        unsigned int mode;

        // Set a 3 digit decimal value
        void setThreeDigit(unsigned int value);

        // Set a 2 digit decimal value
        void setTwoDigit(unsigned int value);

        // Set a 1 digit decimal value
        void setOneDigit(unsigned int value);

    public:

        // Constructor
        Display();
        // Destructor
        ~Display();

        // Setters //
        // Set a decimal numerical value up to 999
        void setVal(unsigned int value, bool redraw);

        // Display P/S depending on mode
        void setMode(unsigned int mode, bool redraw);

        // Show sound level with _ segments
        void setLevel(float level, bool redraw);

        // Set sequence in playback mode, with scrolling seg
        void setPlaybackSeq(std::vector<bool> activeDrums, unsigned int stepNum, bool redraw);

        // Set sequence in stop mode
        void setStopSeq(std::vector<bool> activeDrums, unsigned int page, unsigned int currentDrum, bool redraw);

        // Toggle the REC ENABLE decimal point flash
        void toggleDPFlash(bool redraw);

        // Getters //
        unsigned int getMode();

        unsigned int getDPToggle();
};
} // namespace display
} // namespace drumpi
