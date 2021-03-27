#!/bin/bash
# Startup bash script for the DrumPi

ls /dev/input/by-id/ | grep kbd >| drumpi-config.txt
killall jackd
sleep 2
jackd -dalsa -dhw:2 &
sleep 2
./bin/DrumPi