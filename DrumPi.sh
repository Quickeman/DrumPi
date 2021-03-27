#!/bin/bash
# Startup bash script for the DrumPi

killall jackd
sleep 2
jackd -dalsa -dhw:2 &
sleep 2
./bin/DrumPi