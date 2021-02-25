#include <stdint.h>
#include <vector>
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
        void command(unsigned char reg, unsigned char data);
};

class Display: public Max7219 {
    private:

        // Stores state of DP (on/off)
        bool dpToggle;

        // Display a 3 digit decimal value
        void setThreeDigits(unsigned int value);
        // Display a 2 digit decimal value
        void setTwoDigits(unsigned int value);
        // Display a 1 digit decimal value
        void setOneDigit(unsigned int value);

    public:

        // Constructor
        Display();
        // Destructor
        ~Display();

        // Display a decimal numerical value up to 999
        void showVal(unsigned int value);

        // Display P/S depending on mode
        void showMode(unsigned int mode);

        // Show sound level with _ segments
        void showLevel(float level);

        // Show sequence in playback mode, with scrolling seg
        void showPlaybackSeq(std::vector<bool> activeDrums, unsigned int stepNum);

        // Show sequence in stop mode
        void showStopSeq(std::vector<bool> activeDrums, unsigned int page);

        // Toggle the REC ENABLE decimal point flash
        void toggleDPFlash();
};
} // namespace display
} // namespace drumpi
