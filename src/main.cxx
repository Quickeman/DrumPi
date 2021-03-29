#include <cstdio>
#include <iostream>
#include "config.h.in"
#include "application.hpp"

using namespace drumpi;

int main(int argc, char* argv[]){

    std::cout << std::endl << PROJECT_NAME << " version: " << PROJECT_VER << std::endl;

    Application app;
    app.run();

    return 0;
}
