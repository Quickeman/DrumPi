// File: clock.hpp

#ifndef DRUMPI_CLOCK_H
#define DRUMPI_CLOCK_H

#include "CppTimer.h"

namespace drumpi {
namespace clock {

/*! Converts BPM to miliseconds. */
inline int bpmToMs(int bpm);


/*! Trigger a single delayed action. */
class Timer : public CppTimer {
    public:
        /*! Constructor. */
        Timer();

        /*! Set trigger time in miliseconds.
        \param ms desired trigger time, in miliseconds. */
        void setTime(int ms);

        /*! Returns the trigger time in miliseconds.
        \return trigger time in miliseconds. */
        int getTime();

        /*! Start the timer. */
        void start();

        /*! Callback method run when given time has passed.
        Override to add functionality. */
        virtual void trigger();
    
    private:
        /*! Override event method to call trigger(). */
        void timerEvent() override;

        /*! Trigger time in miliseconds. */
        int time;
};


/*! Trigger repeated actions. */
class Clock : public CppTimer {
    public:
        /*! Constructor. */
        Clock();

        /*! Set the clock rate.
        \param ms desired clocking rate, in miliseconds. */
        void setRate(int ms);

        /*! Returns the clock rate in miliseconds.
        \return clock rate in miliseconds. */
        int getRate();

        /*! Start the clock.
        Default period is 1 second, change with setRate(). */
        void start();

        /*! Callback method run on each clock pulse.
        Override to add functionality. */
        virtual void tick();

    private:
        /*! Override event method to call tick(). */
        void timerEvent() override;

        /*! Clock rate in miliseconds. */
        int rate;
};


/*! Metronome class, similar to Clock but can operate in BPM. */
class Metronome : public Clock {
    public:
        /*! Contructor. */
        Metronome();
        
        /*! Sets the clock rate in BPM.
        \param bpm desired clocking rate, in beats per minute (BPM). */
        void setRateBPM(int bpm);

        /*! Returns the clock rate in BPM.
        \return clock rate in beats per minute (BPM). */
        int getRateBPM();
    
    private:
        /*! Clock rate in BPM.
        Stored to avoid quantisation issues from ms-to-BPM conversion. */
        int bpm;
};

} // namespace clock
} // namespace drumpi

#endif // define DRUMPI_CLOCK_H