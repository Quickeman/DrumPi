//keyboardinput.hpp
//Declaration of keyboard input class
//that detects keyboard presses

#ifndef KEYBOARDINPUT_H
#define KEYBOARDINPUT_H

#include <termios.h>
#include <poll.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>

#include "defs.hpp"
#include "applicationcallback.hpp"

namespace drumpi {

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
    
    /*! Method to set the class called when a keyboard event occurs */
    void connectCallback(ApplicationCallback* app);

    /*! Returns file descriptor of the input device */
    int getFileDescriptor();

    /*! Returns testFlag */
    int getTestFlag();

    /*! Returns the number of key presses detected whilst pollInput was running */
    int getKeyPressCount();

    /*! Running flag used to end the input polling loop */
    int running;

    /*! Callback class called by KeyboardInput when a keyboard event occurs */
    ApplicationCallback* callback;

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
