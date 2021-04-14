#!/bin/bash

# Check for active jackd processes
ps | grep jackd
# If any are active, kill them
if [ $? -eq 0 ]; then
    # Close active jackd processes
    killall -s SIGINT jackd
    # Sleep to allow server time to close
    sleep 1
fi

# Get ID of USB audio interface
ahw_d=$(cat /proc/asound/cards | grep USB | cut -c 2)

# Start jackd
echo "Starting a JACK server..."
jackd -P70 -t2000 -dalsa -dhw:$ahw_d -p128 -n3 -r48000 -s &
# Sleep to allow server to start properly
sleep 2
echo "JACK server started."
