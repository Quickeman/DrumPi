/**
 * @mainpage DrumPi
 * @version 1.0
 * @author Stuart Ball
 * @author Murdo Graham
 * @author Finn Quicke
 * @date April 2021
 */
#include "application.hpp"

#include <iostream>
#include <functional>

using namespace drumpi;

/*! Wrapper for the signal handling lambda expression. */
std::function<void(int)> shutdownHandler;

/*! Global function that can be given as a \ref signal handler.
Calls \ref shutdownHandler. */
void signalHandler(int signal) { shutdownHandler(signal); }

int main(int argc, char* argv[]){

    std::cout << std::endl << PROJECT_NAME << " v" << PROJECT_VERSION << std::endl;

    Application* appPtr;
    signal(SIGINT, signalHandler);
    signal(SIGQUIT, signalHandler);
    signal(SIGTERM, signalHandler);
    signal(SIGHUP, signalHandler);
    signal(SIGKILL, signalHandler);
    signal(SIGTSTP, signalHandler);
    shutdownHandler = [&](int signal) {
        std::cout << "DrumPi: caught signal " << signal << std::endl;
        appPtr->running = false;
    };

    Application app;
    appPtr = &app;

    app.setup();
    app.run();

    return 0;
}
