#include <iostream>
#include "application.hpp"

using namespace drumpi;

int main(int argc, char* argv[]){
    std::cout << "DrumPi v0.1" << std::endl;

    Application app;
    app.run();

    return 0;
}
