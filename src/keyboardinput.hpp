//keyboardinput.hpp
//Declaration of keyboard input class
//that detects keyboard presses

#ifndef KEYBOARDINPUT_H
#define KEYBOARDINPUT_H

#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>

namespace drumpi {
namespace kbdinput {

/*! Class for detecting keyboard presses */
class KeyboardInput {
public:

	/*! /brief Constructor.
	 *
	 * The constructor sets and opens the
	 * device file for the keyboard input device.
	 */
    KeyboardInput();

    /*! Event handler containing information about keyboard input events. */
    struct input_event ev;

    /*! File descriptor for the keyboard device file. */
    int fd;

    /*!
     * Stores error-return codes generated
     * when reading from the keyboard device file.
     */
    size_t n;

    /*!
     * \brief Method to poll the keyboard input.
     *
     * This method monitors the keyboard device file
     * with a polling loop and prints an alert
     * to the terminal when a key is pressed.
     */
    void pollInput();
};

} //namespace kbdinput
} //namespace drumpi

#endif  //KEYBOARDINPUT_H
