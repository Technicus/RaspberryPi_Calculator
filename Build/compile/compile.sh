#!/bin/bash

g++ -Wall -o /home/pi/Calculator/Software/Build/bin/Keypad_Driver /home/pi/Calculator/Software/Keypad_Driver/Build/source/Keypad_Driver_V07.cpp -lwiringPi;
g++ -o /home/pi/Calculator/Software/Build/bin/SimpleCalculator /home/pi/Calculator/Software/Math/source/SimpleCalculator_v02.c -lm -lncurses;

if [ "$(pidof Keypad_Driver)" ] 
then
  # process was found
  sudo kill `pgrep Keypad_Driver`;
else
  # process not found
  echo;
fi

sudo cp /home/pi/Calculator/Software/Build/bin/Keypad_Driver /usr/local/bin/Keypad_Driver;
sudo cp /home/pi/Calculator/Software/Build/bin/SimpleCalculator /usr/local/bin/SimpleCalculator;

sudo /usr/local/bin/Keypad_Driver &
#sudo /usr/local/bin/SimpleCalculator &