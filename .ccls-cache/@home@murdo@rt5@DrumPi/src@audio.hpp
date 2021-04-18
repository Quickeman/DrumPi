// File: audio.hpp
#ifndef DRUMPI_AUDIO_H
#define DRUMPI_AUDIO_H

#include <vector>
#include <string>
#include <memory>

#include <jack/jack.h>

#include "defs.hpp"

namespace drumpi {
namespace audio {

/*! Abstract sample retieval callback class. */
class AudioCallback {
    public:
        /*! Called by a \ref JackClient object when samples are requested by
        Jack.
        \param nSamples the number of samples requested.
        \return a vector of samples, of type \ref sample_t (`float`) */
        virtual std::vector<sample_t> getSamples(int nSamples) = 0;
};

/*! Audio engine class for interacting with the Jack server. */
class JackClient {
    public:
        /*! Constructor.
        Specifies parameters to Jack.
        \param clientName requested client name in Jack.
        \param nOutPorts number of output ports. Default 2.
        \param nInPorts number of input ports. Default 0. */
        JackClient(std::string clientName, int nOutPorts = JackClient::defNumOutPorts, int nInPorts = JackClient::defNumInPorts);

        /*! Destructor.
        Closes the Jack client. */
        ~JackClient();

        /*! Informs Jack that the program is ready to go.
        \param callback \ref AudioCallback object to fetch output samples from.
        \return error code. */
        audioError_t start(AudioCallback& callback);

        /*! Stops the Jack engine.
        \param closeClient whether to close the Jack client or just deactivate 
        it.
        \return error code. */
        audioError_t stop(bool closeClient = true);

        /*! Check if the Jack client is open.
        \return `true` if the client is open. */
        bool isOpen();

        /*! Check if the Jack client is running.
        \return `true` if the client is running. */
        bool isRunning();

        /*! Read method to send output buffer to the Jack server.
        Called by Jack when samples are needed.
        \param nFrames number of frames requested by Jack.
        \param arg pointer to the \ref JackClient (`this`) object.
        \return Jack error code */
        static int _process(jack_nframes_t nFrames, void *arg);

        /*! Shutdown method to exit the program should the Jack server shut down
        or disconnect the client.
        \param arg 0. */
        static void _shutdown(void *arg);
    
    private:
        /*! Pointer to the \ref AudioCallback object that fetches output
        samples. */
        AudioCallback* callback;

        /*! Sets the number of Jack ports.
        \param nOutPorts number of output ports.
        \param nInPorts number of input ports. */
        void setNumPorts(int nOutPorts, int nInPorts);

        /*! Default number of output ports. */
        static const int defNumOutPorts = 2;
        /*! Default number of input ports. */
        static const int defNumInPorts = 0;

        /*! Pointer to the Jack client. */
        jack_client_t *client;
        /*! Jack client name. */
        std::string clientName;
        /*! Jack output ports. */
        std::vector<jack_port_t*> outPorts;
        /*! Jack input ports. Not (yet) implemented. */
        std::vector<jack_port_t*> inPorts;
        /*! Jack ports string. */
        std::vector<std::string> ports;
        /*! Jack options. */
        jack_options_t options = JackNullOption;
        /*! Jack status. */
        jack_status_t jackStatus;

        /*! \ref JackClient error status. */
        audioError_t errorStatus = NO_ERROR;

        /*! Jack client open status. */
        bool open;
        /*! Jack client running status. */
        bool running;
};

} // namespace audio
} // namespace drumpi

#endif // define DRUMPI_AUDIO_H