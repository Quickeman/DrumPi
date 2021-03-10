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

        /**
         * Low level method for writing a data buffer to SPI bus.
         *
         * @param data Buffer containing bytes for writing.
         * @param len Length of bufer in bytes.
         */
        void write(unsigned char *data, unsigned int len);


        /**
         * Sends command data over SPI bus
         */
        void command(unsigned char reg, unsigned char data);

    public:

        /**
         * Constructor
         *
         * @param decodeMode decode mode to be set (default 0x0)
         * @param intensity Intensity to be set (default 0x7)
         * @param scanLimit Scan Limit to be set (default 0x7)
         * @param shutdown Shutdown mode to be set (default 0x1)
         * @param displayTest Display test mode to be set (default 0x0)
         * @param numdigits Number of digits in display (default 8)
         */
        Max7219(unsigned char decodeMode = 0x0,
                unsigned char intensity = 0x7,
                unsigned char scanLimit = 0x7,
                unsigned char shutdown = 0x1,
                unsigned char displayTest = 0x0,
                unsigned int numDigits = 8);

        /**
         * Destructor - deletes any allocated memory and clears display
         */
        ~Max7219();

        /**
         * Sets the value of a digit in the display
         *
         * @param digit Byte address of digit
         * @param value Byte value to assign
         * @param redraw If true, updates all digits at the end of method call
         */
        void setDigit(unsigned char digit, unsigned char value, bool redraw);

        /**
         * Sets the display decode mode
         * @param value Decode mode byte
         */
        void setDecodeMode(unsigned char value);

        /**
         * Sets display intensity
         * @param value Intensity value (1-15)
         */
        void setIntensity(unsigned char value);

        /**
         * Sets display scan limit (number of digits)
         * @param value Scan limit (0-7)
         */
        void setScanLimit(unsigned char value);

        /**
         * Sets shutdown mode on/off
         * @param value Shutdown mode (1/0)
         */
        void setShutdown(unsigned char value);

        /**
         * Sets display mode on/off
         * @param value Display test mode (1/0)
         */
        void setDisplayTest(unsigned char value);

        // Getters

        /**
         * Gets a value of a specified digit
         * @param digit Byte address of digit
         * @returns Current byte value of digit
         */
        unsigned char getDigit(unsigned char digit);

        /**
         * Gets the current decode mode
         * @returns Current decode mode
         */
        unsigned char getDecodeMode();

        /**
         * Gets the current intensity
         * @returns Current intensity
         */
        unsigned char getIntensity();

        /**
         * Gets the current scan limit
         * @returns Current scan limit
         */
        unsigned char getScanLimit();

        /**
         * Gets the current shutdown mode
         * @returns Current shutdown mode
         */
        unsigned char getShutdown();

        /**
         * Gets the current display test mode
         * @returns Current display mode
         */
        unsigned char getDisplayTest();

        /**
         * Gets the number of digits in the display
         * @returns Number of display digits
         */
        unsigned int getNumDigits();

        // Actions

        /**
         * Writes all digit values to display via SPI bus
         */
        void flush();

        /**
         * Resets all digit values to 0
         * @param redraw If true, writes updated values to display
         */
        void clear(bool redraw);

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
        const unsigned char upperSqAddr = 0x63;
        const unsigned char bottomAddr = 0x8;

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

        void setActiveDrums(std::vector<bool> activeDrums, unsigned int page);

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
