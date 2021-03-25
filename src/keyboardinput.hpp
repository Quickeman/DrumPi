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

#include "defs.hpp"

namespace drumpi {

/*! Abstract application callback class */
class ApplicationCallback {
public:
    /*! Virtual functions to be overridden by derived class */
    virtual void interpretKeyPress(int key) = 0;
    virtual void setState(stateLabel_t newstate) = 0;
    virtual drumID_t interpretDrumKey(int key) = 0;
};


/*! Class for detecting keyboard presses */
class KeyboardInput {

public:

	/*! /brief Constructor.
	 *
	 * The constructor sets and opens the
	 * device file for the keyboard input device.
	 */
    KeyboardInput();

    /*!
     * \brief Method to poll the keyboard input.
     *
     * This method monitors the keyboard device file
     * with a polling loop and prints an alert
     * to the terminal when a key is pressed.
     */
    void pollInput();

    /*! Returns file descriptor of the input device */
    int getFileDescriptor();

    /*! Returns testFlag */
    int getTestFlag();

    /*! Returns the number of key presses detected whilst pollInput was running */
    int getKeyPressCount();

    /*! Running flag used to end the input polling loop */
    int running;

    /*! Flag indicating that a key has been pressed and requires processing */
    int keyPressedFlag;

    /*!
     * \brief Variable storing which key was pressed.
	 * 
	 * Key values are defined in linux/input-event-codes,
	 * included in linux/input.h.
     */
    int keyPressed;

private:

    /*! Event handler containing information about keyboard input events */
    struct input_event ev;

    /*! Array of pollfd structs checked by poll() system call */
    struct pollfd fdset[1];

    /*! File descriptor for the keyboard device file */
    int fd;

    /*! Flag to check pollInput has been called successfully */
    int testFlag;

    /*! 
     * Test variable to count number of key presses
     * detected whilst pollInput is running
     */
    int keyPressCount;

};

} //namespace drumpi

#endif  //KEYBOARDINPUT_H
