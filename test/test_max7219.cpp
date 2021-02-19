#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SequencerTest
#include <boost/test/unit_test.hpp>
#include <max7219.hpp>
extern "C" {
#include <wiringPiSPI.h>
}

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
    Max7219 display(0x0, 0x5, 0x3, 0x1, 0x0);
    BOOST_TEST(display.getDecodeMode() == 0x0);
    BOOST_TEST(display.getIntensity() == 0x5);
    BOOST_TEST(display.getScanLimit() == 0x3);
    BOOST_TEST(display.getShutdown() == 0x1);
    BOOST_TEST(display.getDisplayTest() == 0x0);
}
