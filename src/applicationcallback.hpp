//applicationcallback.hpp

#ifndef APPLICATIONCALLBACK_H
#define APPLICATIONCALLBACK_H

#include "defs.hpp"

namespace drumpi {

/*! Abstract application callback class */
class ApplicationCallback {
public:
    /*! Virtual functions to be overridden by derived class */
    virtual void interpretKeyPress(int key) = 0;
    virtual void setState(stateLabel_t newstate) = 0;
    
    /*! running flag for the application */
    bool running;
};

} //namespace drumpi

#endif  //APPLICATIONCALLBACK_H
