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

/*! Class for monitoring a keyboard device file and detecting keyboard presses. */
class KeyboardInput {

public:

	/*! \brief Constructor.
	 *
	 * The constructor detects and opens the
	 * device file for the keyboard input device.
	 */
    KeyboardInput();

    /*!
     * \brief Polls the keyboard input for events.
     *
     * This method monitors the keyboard device file
     * with a polling loop and calls the \ref Application object
     * to interpret the key press and perform an action
     * when a key press is detected.
     */
    void pollInput();
    
    /*! 
     * \brief Sets the \ref Application object called when a keyboard event occurs.
     * 
     * \param app \ref Application object called by pollInput
     * when a key press is detected.
     * */
    void connectCallback(ApplicationCallback* app);

    /*! \returns file descriptor \ref fd of the input device. */
    int getFileDescriptor();

    /*! \returns \ref testFlag. */
    int getTestFlag();

    /*! Running flag used to end the input polling loop. */
    int running;

    /*! Callback class called by KeyboardInput when a keyboard event occurs. */
    ApplicationCallback* callback;

private:

    /*! Event handler containing information about keyboard input events. */
    struct input_event ev;

    /*! Array of pollfd structs checked by poll() system call. */
    struct pollfd fdset[1];

    /*! File descriptor for the keyboard device file. */
    int fd;

    /*! Flag to check \ref pollInput has been called successfully. */
    int testFlag;

};

} //namespace drumpi

#endif  //KEYBOARDINPUT_H
