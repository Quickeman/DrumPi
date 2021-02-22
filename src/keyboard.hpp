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

namespace drumpi {
namespace kbdinput {

//class for detecting keyboard presses
class KeyboardInput {
public:
    KeyboardInput();	//constructor

    struct input_event ev;
    int fd;
    size_t n;

    void pollInput();
};

} //namespace kbdinput
} //namespace drumpi

#endif  //KEYBOARDINPUT_H
