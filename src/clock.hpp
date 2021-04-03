// File: clock.hpp

#ifndef DRUMPI_CLOCK_H
#define DRUMPI_CLOCK_H

#include "CppTimer.h"

namespace drumpi {
namespace clock {

/*! Converts BPM to ms. */
inline int bpmToMs(int bpm) {
    return 60000 / bpm;
}


/*! Trigger a single delayed action. */
class Timer : public CppTimer {
    public:
        /*! Constructor. */
        Timer();

        /*! Destructor.
        Deactivates the timer. */
        ~Timer();

        /*! Set trigger time in ms.
        \param ms desired trigger time, in ms. */
        void setTime(int ms);

        /*! Returns the trigger time in ms.
        \return trigger time in ms. */
        int getTime();

        /*! Start the timer. */
        void start();

        /*! Cancels the timer. */
        void stop();

        /*! Checks if the `Timer` is active.
        \return `true` if active. */
        bool isActive();

        /*! Callback method run when given time has passed.
        Override to add functionality. */
        virtual void trigger() = 0;
    
    private:
        /*! Override event method to call trigger(). */
        void timerEvent() override;

        /*! Trigger time in ms. */
        int time;

        /*! Active flag. */
        bool active;
};


/*! Trigger repeated actions. */
class Clock : public CppTimer {
    public:
        /*! Constructor. */
        Clock();

        /*! Destructor.
        Deactivates the clock. */
        ~Clock();

        /*! Set the clock rate.
        \param ms desired clocking rate, in ms. */
        void setRate(int ms);

        /*! Returns the clock rate in ms.
        \return clock rate in ms. */
        int getRate();

        /*! Start the clock.
        Default period is 1 second, change with setRate(). */
        void start();

        /*! Stop the clock. */
        void stop();

        /*! Checks if the `Clock` is active.
        \return `true` if active. */
        bool isActive();

        /*! Callback method run on each clock pulse.
        Override to add functionality. */
        virtual void tick() = 0;

    private:
        /*! Override event method to call tick(). */
        void timerEvent() override;

        /*! Clock rate in ms. */
        int rate;

        /*! Active flag. */
        bool active;

    protected:
        /*! Flag for the clocking rate being changed. */
        bool rateChangeFlag;
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