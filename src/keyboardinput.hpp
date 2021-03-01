//keyboardinput.hpp
//Declaration of keyboard input class
//that detects keyboard presses

#ifndef KEYBOARDINPUT_H
#define KEYBOARDINPUT_H

#include <poll.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>

namespace drumpi {
namespace keyboard {

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

    /*! Array of pollfd structs checked by poll() system call */
    struct pollfd fdset[1];

    /*! File descriptor for the keyboard device file. */
    int fd;

    /*!
     * Stores error-return codes generated
     * when reading from the keyboard device file.
     */
    size_t n;

    /*! Running flag used to control input polling loop */
    int running;

    /*! Flag to check pollInput has been called successfully */
    int testflag;

    /*! 
     * Test variable to count number of key presses
     * whilst pollInput is running
     */
    int keypresscount;

    /*!
     * \brief Method to poll the keyboard input.
     *
     * This method monitors the keyboard device file
     * with a polling loop and prints an alert
     * to the terminal when a key is pressed.
     */
    void pollInput();
};

} //namespace keyboard
} //namespace drumpi

#endif  //KEYBOARDINPUT_H