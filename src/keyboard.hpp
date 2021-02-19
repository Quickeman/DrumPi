//keyboard.hpp
//Declaration of keyboard input class
//that detects keyboard presses

#ifndef KEYBOARDINPUT_H
#define KEYBOARDINPUT_H

#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>

//class for detecting keyboard presses
class KeyboardInput {
public:
    KeyboardInput()	//constructor
    {
        const char *input_file = "/dev/input/event3";
        fd = open(input_file, O_RDONLY);
    }

    struct input_event ev;
    int fd;
    size_t n;

    void poll_input();
};

#endif  //KEYBOARDINPUT_H