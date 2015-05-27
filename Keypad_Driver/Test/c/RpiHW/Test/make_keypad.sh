#!/bin/bash
#g++ `pkg-config --libs --cflags rpi-hw` keyPad_V00.cpp -o keyPad_V00
g++ `pkg-config --libs --cflags rpi-hw` 16keys2_V00.cpp -o 16keys2_V00