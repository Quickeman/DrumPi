#include <stdint.h>
#include <vector>
#include <math.h>
#include <defs.hpp>
#include <wiringPiSPI.h>
#include <clock.hpp>
#include <memory>

namespace drumpi {

class Max7219
{
    private:

        // Number of digits
        unsigned int numDigits;

        // Command register variables
        unsigned char 
            decodeMode,
            intensity,
            scanLimit,
            shutdown,
            displayTest;
    
        /**
         * Buffer to contain each digit's value
         */
        std::vector<unsigned char> digitBuffer;

        /**
         * Low level method for writing a data buffer to SPI bus.
         * Should not be used by host application.
         * Instead use digit setters and flush commands.
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

        // SETTERS //

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

        // GETTERS //

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

        // HIGH LEVEL METHODS //

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

        // Hex adresses for commonly used segments
        const unsigned char dpAddr = 0x80;
        const unsigned char upperSqAddr = 0x63;
        const unsigned char bottomAddr = 0x8;

        /** Vector to contain key mappings
         *
         * keyMapping[drumID] = key/digit
         */
        std::vector<unsigned int> keyMapping = {
            3,  // Kick
            2,  // Snare
            4,  // Clap
            5,  // HH Close
            6,  // HH Open
            0,  // Tom 1
            1,  // Tom 2
            7,  // Cymbal
        };

        /** Set a 3 digit decimal value
         * @param value 3 digit value to set
         */
        void setThreeDigit(unsigned int value);

        /** Set a 2 digit decimal value
         * @param value 2 digit value to set
         */
        void setTwoDigit(unsigned int value);

        /** Set a 1 digit decimal value
         * @param value 1 digit value to set
         */
        void setOneDigit(unsigned int value);

        /**
         * Sets digits to show active drums of a given sequence and page
         *
         * @param activeDrums Vector of bools representing sequence
         * @param page 8 digit page to display
         */
        void setActiveDrums(std::vector<bool> activeDrums, unsigned int page);

        /**
         * Updates display to show audio level between -1 and 1
         * @param level Audio level to display
         */
        void addLevel(float level);

    public:

        Display(); /// Constructor

        ~Display(); /// Destructor

        // SETTERS //

        /**
         * Sets digits to display a number up to 999
         *
         * @param value Numerical value to display
         * @param redraw If true, updates display
         */
        void setVal(unsigned int value, bool redraw);

        /**
         * Sets the mapping of drums to keys
         * Ensuring that the correct digits are displayed
         * 
         * @param _keyMapping The given mapping to set
         */
        void setKeymapping(std::vector<unsigned int> _keyMapping);

        /**
         * Updates display to show sequence in playback mode
         *
         * @param activeDrums Vector of bools representing sequence
         * @param stepNum Current step in sequence
         * @param redraw If true, updates display
         */
        void setPlaybackSeq(std::vector<bool> activeDrums, unsigned int stepNum, bool redraw);

        /**
         * Updates display to show sequence in stop mode
         *
         * @param activeDrums Vector of bools representing sequence
         * @param page Current page to display
         * @param currentDrum Active drum for editing
         * @param redraw If true, updates display
         */
        void setStopSeq(std::vector<bool> activeDrums, unsigned int page, unsigned int currentDrum, bool redraw);

        /**
         * Updates performance mode display
         * 
         * @param activeDrums Vector containing drum IDs of all current drums
         * @param level Audio level
         * @param redraw If true, updates display
         */
        void setPerformance(std::vector<drumID_t> activeDrums, float level, bool redraw);
        /**
         * Returns a key mapping
         * @param index DrumId to query
         * */
        int getKeymapping(int index);
    };
};

/*! \ref Metronome derived class to clock a \ref Display. */
class DisplayClock : public clock::Clock {
    public:
        /*! Constructor.
        Sets the Display to be clocked.
        \param s \ref Display object to be clocked. */
        DisplayClock(Display* d);

        /*! Override the tick method.
        Clocks the \ref Display given to \ref setDisplay. */
        void tick() override;
    
    private:
        /*! Pointer to the `Display` object to be clocked. */
        Display* display = nullptr;

    };

} // namespace drumpi
