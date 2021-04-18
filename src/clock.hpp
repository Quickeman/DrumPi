// File: clock.hpp

#ifndef DRUMPI_CLOCK_H
#define DRUMPI_CLOCK_H

#include "CppTimer.h"

namespace drumpi {
/*! The namespace for timing related items. */
namespace clock {

/*! Converts BPM to ms.
\param bpm BPM value to convert to ms.
\return period of BPM in ms. */
inline int bpmToMs(int bpm) {
    return 60000 / bpm;
}


/*! Trigger a single delayed action.
To use, create a class that inherits from this and override the \ref trigger
method to set the functionality. */
class Timer : public CppTimer {
    public:
        /*! Constructor. */
        Timer();

        /*! Destructor.
        Deactivates the \ref Timer. */
        ~Timer();

        /*! Set trigger time in ms.
        \param ms desired trigger time in ms. */
        void setTime(int ms);

        /*! Returns the trigger time in ms.
        \return trigger time in ms. */
        int getTime();

        /*! Start the \ref Timer. */
        void start();

        /*! Cancels the \ref Timer. */
        void stop();

        /*! Checks if the \ref Timer is active.
        \return `true` if active. */
        bool isActive();

        /*! Callback method run when the time has passed.
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


/*! Trigger repeated actions.
To use, create a class that inherits from this and override the \ref tick method
to set the functionality. */
class Clock : public CppTimer {
    public:
        /*! Constructor. */
        Clock();

        /*! Destructor.
        Deactivates the clock. */
        ~Clock();

        /*! Set the clock rate.
        The change takes effect on the next \ref tick, or can be forced by
        calling \ref stop and then \ref start.
        \param ms desired clocking rate in ms. */
        void setRate(int ms);

        /*! Returns the clock rate in ms.
        \return clock rate in ms. */
        int getRate();

        /*! Start the clock.
        Default period is 1 second, change with \ref setRate. */
        void start();

        /*! Stop the clock. */
        void stop();

        /*! Checks if the \ref Clock is active.
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


/*! Metronome class, similar to \ref Clock but can operate in BPM.
To use, create a class that inherits from this and override the \ref tick method
to set the functionality. */
class Metronome : public Clock {
    public:
        /*! Contructor. */
        Metronome();

        /*! Sets the clock rate in BPM.
        The change takes effect on the next \ref tick, or can be forced by
        calling \ref stop and then \ref start.
        \param bpm desired clocking rate in BPM. */
        void setRateBPM(int bpm);

        /*! Returns the clock rate in BPM.
        \return clock rate in BPM. */
        int getRateBPM();
    
    private:
        /*! Clock rate in BPM.
        Stored to avoid quantisation issues from ms-to-BPM conversion. */
        int bpm;
};

} // namespace clock
} // namespace drumpi

#endif // define DRUMPI_CLOCK_H