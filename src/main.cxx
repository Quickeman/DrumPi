#include "application.hpp"

#include <iostream>
#include <functional>

using namespace drumpi;

std::function<void(int)> shutdownHandler;
void signalHandler(int signal) { shutdownHandler(signal); }

int main(int argc, char* argv[]){
    std::cout << "DrumPi v0.1" << std::endl;

    Application* appPtr;
    signal(SIGINT, signalHandler);
    shutdownHandler = [&](int signal) {
        std::cout << "DrumPi: caught signal " << signal << std::endl;
        appPtr->running = false;
    };

    Application app;
    appPtr = &app;
    
    app.run();

    return 0;
}
