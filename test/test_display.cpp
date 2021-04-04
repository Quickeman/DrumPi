#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SequencerTest
#include <boost/test/unit_test.hpp>
#include <display.hpp>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <defs.hpp>

using namespace drumpi;

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
}


BOOST_AUTO_TEST_CASE(show_num) {
    int displayVal = 619;
    Display display;
    display.setVal(displayVal, true);

    //Test each digit
    BOOST_TEST(display.getDigit(7) == 0x5F);
    BOOST_TEST(display.getDigit(6) == 0x30);
    BOOST_TEST(display.getDigit(5) == 0x7B);
    BOOST_TEST(display.getDigit(4) == 0x00);
}



BOOST_AUTO_TEST_CASE(setStopSeq) {
    Display display;
    std::vector<bool> sequence = {1,0,0,0,1,0,0,0, 0,0,1,0,1,0,1,0};
    display.setStopSeq(sequence, 0, 2, true);
    BOOST_TEST(display.getDigit(7) == 0x63);
    BOOST_TEST(display.getDigit(6) == 0x80);
    BOOST_TEST(display.getDigit(5) == 0x0);
    BOOST_TEST(display.getDigit(4) == 0x0);
    BOOST_TEST(display.getDigit(3) == 0x63);
    BOOST_TEST(display.getDigit(2) == 0x0);
    BOOST_TEST(display.getDigit(1) == 0x0);
    BOOST_TEST(display.getDigit(0) == 0x0);

    display.setStopSeq(sequence, 1, 8, true);
    BOOST_TEST(display.getDigit(7) == 0x0);
    BOOST_TEST(display.getDigit(6) == 0x0);
    BOOST_TEST(display.getDigit(5) == 0x63);
    BOOST_TEST(display.getDigit(4) == 0x0);
    BOOST_TEST(display.getDigit(3) == 0x63);
    BOOST_TEST(display.getDigit(2) == 0x0);
    BOOST_TEST(display.getDigit(1) == 0x63);
    BOOST_TEST(display.getDigit(0) == 0x80);
}

BOOST_AUTO_TEST_CASE(setPlaybackSeq) {
    Display display;
    std::vector<bool> sequence = {1,0,0,0,1,0,0,0, 0,0,1,0,1,0,1,0};
    display.setPlaybackSeq(sequence, 1, true);
    BOOST_TEST(display.getDigit(7) == 0x6B);
    BOOST_TEST(display.getDigit(6) == 0x0);
    BOOST_TEST(display.getDigit(5) == 0x0);
    BOOST_TEST(display.getDigit(4) == 0x0);
    BOOST_TEST(display.getDigit(3) == 0x63);
    BOOST_TEST(display.getDigit(2) == 0x0);
    BOOST_TEST(display.getDigit(1) == 0x0);
    BOOST_TEST(display.getDigit(0) == 0x0);

    display.setPlaybackSeq(sequence, 15, true);
    BOOST_TEST(display.getDigit(7) == 0x0);
    BOOST_TEST(display.getDigit(6) == 0x0);
    BOOST_TEST(display.getDigit(5) == 0x63);
    BOOST_TEST(display.getDigit(4) == 0x0);
    BOOST_TEST(display.getDigit(3) == 0x63);
    BOOST_TEST(display.getDigit(2) == 0x0);
    BOOST_TEST(display.getDigit(1) == 0xE3);
    BOOST_TEST(display.getDigit(0) == 0x0);
}

BOOST_AUTO_TEST_CASE(setKeyMapping) {
    Display display;
    std::vector<unsigned int> newMapping = {
        0,
        1,
        2,
        3,
        4,
        5,
        6,
        7,
    };

    display.setKeymapping(newMapping);
    BOOST_TEST(display.getKeymapping(0) == 0);
    BOOST_TEST(display.getKeymapping(1) == 1);
    BOOST_TEST(display.getKeymapping(2) == 2);
    BOOST_TEST(display.getKeymapping(3) == 3);
    BOOST_TEST(display.getKeymapping(4) == 4);
    BOOST_TEST(display.getKeymapping(5) == 5);
    BOOST_TEST(display.getKeymapping(6) == 6);
    BOOST_TEST(display.getKeymapping(7) == 7);
}

BOOST_AUTO_TEST_CASE(showPerformance) {
    Display display;
    std::vector<drumID_t> drumsActive = {drumID_t(5), drumID_t(1), drumID_t(2), drumID_t(4)};
    display.setPerformance(drumsActive, 0.9, true);
    BOOST_TEST(display.getDigit(7) == 0x6B);
    BOOST_TEST(display.getDigit(6) == 0x8);
    BOOST_TEST(display.getDigit(5) == 0x6B);
    BOOST_TEST(display.getDigit(4) == 0x8);
    BOOST_TEST(display.getDigit(3) == 0x6B);
    BOOST_TEST(display.getDigit(2) == 0x8);
    BOOST_TEST(display.getDigit(1) == 0x6B);
    BOOST_TEST(display.getDigit(0) == 0x8);

}
