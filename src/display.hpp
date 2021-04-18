#include <stdint.h>
#include <vector>
#include <math.h>
#include <defs.hpp>
#include <wiringPiSPI.h>
#include <clock.hpp>
#include <applicationcallback.hpp>
#include <memory>

namespace drumpi {

/**
 * Low level driver for the Max7219
 * 7-segment display driver
 */
class Max7219
{
    private:

        /** Number of digits. */
        unsigned int numDigits;

        /** Display decode mode. */
        unsigned char decodeMode;

        /** Display intensity. */
        unsigned char intensity;

        /** Display scan limit. */
        unsigned char scanLimit;

        /** Display shutdown mode. */
        unsigned char shutdown;

        /** Display display test mode. */
        unsigned char displayTest;

        /** Buffer to contain each digit's value. */
        std::vector<unsigned char> digitBuffer;

        /**
         * Low level method for writing a data buffer to SPI bus.
         * Should not be used by host application.
         * Instead use \ref setDigit and \ref flush methods.
         *
         * @param data Buffer containing bytes for writing.
         * @param len Length of buffer in bytes.
         */
        void write(unsigned char *data, unsigned int len);

        /**
         * Sends command data over SPI bus.
         */
        void command(unsigned char reg, unsigned char data);

    public:

        /**
         * Constructor
         *
         * @param decodeMode decode mode to be set. (default 0x0)
         * @param intensity Intensity to be set. (default 0x7)
         * @param scanLimit Scan Limit to be set. (default 0x7)
         * @param shutdown Shutdown mode to be set. (default 0x1)
         * @param displayTest Display test mode to be set. (default 0x0)
         * @param numDigits Number of digits in display. (default 8)
         */
        Max7219(unsigned char decodeMode = 0x0,
                unsigned char intensity = 0x7,
                unsigned char scanLimit = 0x7,
                unsigned char shutdown = 0x1,
                unsigned char displayTest = 0x0,
                unsigned int numDigits = 8);

        /**
         * Destructor - deletes any allocated memory and clears display.
         */
        ~Max7219();

        // SETTERS //

        /**
         * Sets a value in the \ref digitBuffer.
         *
         * @param digit Byte address of digit.
         * @param value Byte value to assign.
         * @param redraw If true, updates all digits at the end of method call.
         */
        void setDigit(unsigned char digit, unsigned char value, bool redraw);

        /**
         * Sets the \ref decodeMode.
         * @param value Decode mode byte.
         */
        void setDecodeMode(unsigned char value);

        /**
         * Sets the \ref intensity.
         * @param value Intensity value (1-15).
         */
        void setIntensity(unsigned char value);

        /**
         * Sets the \ref scanLimit.
         * @param value Scan limit (0-7).
         */
        void setScanLimit(unsigned char value);

        /**
         * Sets the \ref shutdown mode.
         * @param value Shutdown mode (1/0).
         */
        void setShutdown(unsigned char value);

        /**
         * Sets the \ref displayTest mode.
         * @param value Display test mode (1/0).
         */
        void setDisplayTest(unsigned char value);

        // GETTERS //

        /**
         * Gets a value of a digit in the \ref digitBuffer.
         * @param digit Byte address of digit.
         * @returns Current byte value of digit.
         */
        unsigned char getDigit(unsigned char digit);

        /**
         * Gets the current \ref decodeMode.
         * @returns Current \ref decodeMode.
         */
        unsigned char getDecodeMode();

        /**
         * Gets the current \ref intensity.
         * @returns Current \ref intensity.
         */
        unsigned char getIntensity();

        /**
         * Gets the current \ref scanLimit.
         * @returns Current \ref scanLimit.
         */
        unsigned char getScanLimit();

        /**
         * Gets the current \ref shutdown mode.
         * @returns Current \ref shutdown mode.
         */
        unsigned char getShutdown();

        /**
         * Gets the current \ref displayTest mode.
         * @returns Current \ref displayTest mode.
         */
        unsigned char getDisplayTest();

        /**
         * Gets the number of digits in the display.
         * @returns Number of display digits.
         */
        unsigned int getNumDigits();

        // HIGH LEVEL METHODS //

        /**
         * Writes all \ref digitBuffer values to display via SPI bus.
         */
        void flush();

        /**
         * Resets all digits in the \ref digitBuffer to 0.
         * @param redraw If true, calls \ref flush to update display.
         */
        void clear(bool redraw);

};

/**
 * High level DrumPi display driver
 */
class Display: public Max7219 {

    private:

        /** Vector to contain corresponding hex values
         * for decimal digit representation.
         *
         * Prevents the need to toggle Code B decode
         * for every numerical display.
         */
        const std::vector<unsigned char> decHexVals = {
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

        /** Hex address for decimal place. */
        const unsigned char dpAddr = 0x80;
        /** Hex address for upper square. */
        const unsigned char upperSqAddr = 0x63;
        /** Hex address for bottom underscore segment. */
        const unsigned char bottomAddr = 0x8;

        /** Vector to contain key mappings.
         *
         * keyMapping[drumID] = key/digit.
         */
        std::vector<unsigned int> keyMapping = {
            0,  // Kick
            1,  // Snare
            2,  // Clap
            3,  // HH Close
            4,  // HH Open
            5,  // Tom 1
            6,  // Tom 2
            7,  // Cymbal
        };

        /** Sets a 3 digit decimal value.
         * @param value 3 digit value to set.
         */
        void setThreeDigit(unsigned int value);

        /** Sets a 2 digit decimal value.
         * @param value 2 digit value to set.
         */
        void setTwoDigit(unsigned int value);

        /** Sets a 1 digit decimal value.
         * @param value 1 digit value to set.
         */
        void setOneDigit(unsigned int value);

        /**
         * Sets values in the \ref digitBuffer
         * to show active drums for a given sequence and page.
         *
         * @param activeDrums Vector of bools representing sequence.
         * @param page 8 digit page to display.
         */
        void setActiveDrums(std::vector<bool> activeDrums, unsigned int page);

        /**
         * Adds to values in \ref digitBuffer
         * to show an audio level.
         *
         * Not implemented in V1.0.
         * @param level Audio level to display.
         */
        void addLevel(float level);

        /**
         * Adds to values in \ref digitBuffer
         * to show the current page.
         *
         * @param page Page to display.
         */
        void addPage(unsigned int page);

    public:

        Display(); /// Constructor.

        ~Display(); /// Destructor.

        // SETTERS //

        /**
         * Sets values in \ref digitBuffer
         * to display a number up to 999.
         *
         * @param value Numerical value to display.
         * @param redraw If true, updates display.
         */
        void setVal(unsigned int value, bool redraw);

        /**
         * Sets values in \ref digitBuffer
         * to display a drum volume and current drum.
         *
         * @param value Numerical value to display.
         * @param currentDrum Current drum to display.
         * @param redraw If true, updates display.
         */
        void setDrumVolume(unsigned int value, drumID_t currentDrum, bool redraw);

        /**
         * Sets the mapping of drums to keys.
         * Ensuring that the correct digits are displayed.
         *
         * Currently unused in v1.0.
         *
         * @param _keyMapping The given mapping to set.
         */
        void setKeymapping(std::vector<unsigned int> _keyMapping);

        /**
         * Sets values in \ref digitBuffer
         * to show sequence in playback mode.
         *
         * @param activeDrums Vector of bools representing sequence.
         * @param stepNum Current step in sequence.
         * @param redraw If true, updates display.
         */
        void setPlaybackSeq(std::vector<bool> activeDrums, unsigned int stepNum, bool redraw);

        /**
         * Sets values in \ref digitBuffer
         * to show sequence in stop mode.
         *
         * @param activeDrums Vector of bools representing sequence.
         * @param page Current page to display.
         * @param currentDrum Active drum for editing.
         * @param redraw If true, updates display.
         */
        void setStopSeq(std::vector<bool> activeDrums, unsigned int page, drumID_t currentDrum, bool redraw);

        /**
         * Sets values in \ref digitBuffer
         * to show performance display.
         *
         * @param activeDrums Vector containing \ref drumID_t of all current drums.
         * @param level Audio level.
         * @param redraw If true, updates display.
         */
        void setPerformance(std::vector<drumID_t> activeDrums, float level, bool redraw);

        /**
         * Returns a key mapping.
         * @param index DrumId to query.
         * */
        int getKeymapping(int index);
    };
}
