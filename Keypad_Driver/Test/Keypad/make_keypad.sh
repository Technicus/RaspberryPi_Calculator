#!/bin/bash
#g++ `pkg-config --libs --cflags rpi-hw` -v 12keys01.cpp -o 12keys01
g++ `pkg-config --libs --cflags rpi-hw` -v 12keys03.cpp -o 12keys03
