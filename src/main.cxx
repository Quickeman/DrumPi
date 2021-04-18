/**
 * @mainpage DrumPi
 * @brief A drum machine made for the Raspberry Pi.
 * @version 1.0
 * @authors Stuart Ball     <2260112B@student.gla.ac.uk>
 * @authors Murdo Graham    <2261517G@student.gla.ac.uk>
 * @authors Finn Quicke     <2256694Q@student.gla.ac.uk>
 * @date April 2021
 */
#include "application.hpp"

#include <iostream>
#include <functional>

using namespace drumpi;

/*! Wrapper for the signal handling lambda expression. */
std::function<void(int)> shutdownHandler;

/*! Global function that can be given as a signal handler.
Calls \ref shutdownHandler. */
void signalHandler(int signal) { shutdownHandler(signal); }

/*! Main function of execution. */
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
