#!/bin/bash

# Detect USB keyboard
ls /dev/input/by-id/ | grep kbd >| kbd-config.txt
