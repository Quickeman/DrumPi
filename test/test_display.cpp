#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SequencerTest
#include <boost/test/unit_test.hpp>
#include <display.hpp>
extern "C" {
#include <wiringPiSPI.h>
}

using namespace drumpi;
using namespace display;

BOOST_AUTO_TEST_CASE(constructors) {
    Max7219 display;
    BOOST_CHECK(&display);
}

BOOST_AUTO_TEST_CASE(defaults) {
    Max7219 display;
    BOOST_TEST(display.getDecodeMode() == 0x0);
    BOOST_TEST(display.getIntensity() == 0x7);
    BOOST_TEST(display.getScanLimit() == 0x7);
    BOOST_TEST(display.getShutdown() == 0x1);
    BOOST_TEST(display.getDisplayTest() == 0x0);
}

BOOST_AUTO_TEST_CASE(custom_agrs) {
    Max7219 display(0x0, 0x5, 0x7, 0x1, 0x1);
    BOOST_TEST(display.getDecodeMode() == 0x0);
    BOOST_TEST(display.getIntensity() == 0x5);
    BOOST_TEST(display.getScanLimit() == 0x7);
    BOOST_TEST(display.getShutdown() == 0x1);
    BOOST_TEST(display.getDisplayTest() == 0x1);
}

BOOST_AUTO_TEST_CASE(reg_setters) {
    // Max7219 object with default params
    Max7219 display;
    display.setDecodeMode(0x1);
    BOOST_TEST(display.getDecodeMode() == 0x1);

    display.setIntensity(0x9);
    BOOST_TEST(display.getIntensity() == 0x9);

    display.setScanLimit(0x4);
    BOOST_TEST(display.getScanLimit() == 0x4);

    display.setShutdown(0x0);
    BOOST_TEST(display.getShutdown() == 0x0);

    display.setDisplayTest(0x1);
    BOOST_TEST(display.getDisplayTest() == 0x1);
}

BOOST_AUTO_TEST_CASE(digit_setter) {
   Max7219 display;
   for(unsigned char value = 0x0; value < 0xFF; value ++) {
        for(unsigned char digit = 0x00; digit < 0x8; digit ++) {
            display.setDigit(digit, value, false);
            BOOST_TEST(display.getDigit(digit) == value);
        }
        display.flush();
    }
    //display.clear(true);
    //display.setDigit(0x1, 0xF, true);
    //display.flush();
    //display.clear(true);
}
