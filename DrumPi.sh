#!/bin/bash

# Detect USB keyboard
ls /dev/input/by-id/ | grep kbd >| kbd-config.txt

# Close any active JACK servers
killall -s SIGINT jackd
# Sleep to allow server closing
sleep 1

# Start jackd
echo "Starting a JACK server..."
jackd -P70 -t2000 -dalsa -dhw:2 -p128 -n3 -r48000 -s &
# Sleep to allow server to start properly
sleep 2
echo "JACK server started."

# Start the DrumPi program
echo "Starting DrumPi..."
./bin/DrumPi

# When DrumPi has been quit, say goodbye
printf "\nDrumPi closed.\n"

# Close jackd
echo "Closing the JACK server..."
killall -s SIGINT jackd

# Pause to let bash catch its breath
sleep 1

# Inform the user the JACK server has closed
echo "JACK server closed."

