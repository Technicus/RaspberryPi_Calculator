/* 
    Title --- 12keys0.cpp [examples]

    Copyright (C) 2013 Giacomo Trudu - wicker25[at]gmail[dot]com

    This file is part of Rpi-hw.

    Rpi-hw is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation version 3 of the License.

    Rpi-hw is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Rpi-hw. If not, see <http://www.gnu.org/licenses/>.
*/


#include <iostream>
#include <stdlib.h>

// Include Rpi-hw headers
#include <rpi-hw.hpp>
#include <rpi-hw/time.hpp>
#include <rpi-hw/keypad/matrix.hpp>

// Use Rpi-hw namespace
using namespace rpihw;

/*
      (21, 10, 4)     colums = 3
          |||
   -----------------
   | (1)  (2)  (3) |
   |               |
   | (4)  (5)  (6) |
   |               |
   | (7)  (8)  (9) |
   |               |
   | (*)  (0)  (#) |
   -----------------
          ||||
    (22, 14, 15, 17)  rows = 4
*/

int
main( int argc, char *args[] ) {

	// Matrix keypad controller
	keypad::matrix dev( { 21, 22, 23 }, { 16, 17, 18, 19 } );

	// Main loop
	for ( ;; ) {

		// Check some buttons state
		if ( dev.pressed(0) )
			std::cout << "0\n";
      if ( dev.pressed(1) )
         std::cout << "1\n";
      if ( dev.pressed(2) )
         std::cout << "2\n";
      if ( dev.pressed(3) )
         std::cout << "3\n";
      if ( dev.pressed(4) )
         std::cout << "4\n";
      if ( dev.pressed(5) )
         std::cout << "5\n";
      if ( dev.pressed(6) )
         std::cout << "6\n";
      if ( dev.pressed(7) )
         std::cout << "7\n";
      if ( dev.pressed(8) )
         std::cout << "8\n";
      if ( dev.pressed(9) )
         std::cout << "9\n";
      if ( dev.pressed(10) )
         std::cout << "10\n";
      if ( dev.pressed(11) )
         std::cout << "11\n";

      //if ( dev.released(2) )
      //   std::cout << "You have released button 2!\n";
         
      if ( dev.pressed(1) && dev.pressed(4) )
         std::cout << "You have pressed buttons 1 and 4!\n";
      
      if ( dev.pressed(0) && dev.pressed(2) ){
         std::cout << "You have pressed buttons 0 and 2!\n . . . keypad shutdown . . .\n";
         system ("sudo shutdown -h now");
      }
      
      if ( dev.pressed(9) && dev.pressed(11) ){
         std::cout << "You have pressed buttons 9 and 11!\n . . . keypad rebooting . . .\n";
         system ("sudo reboot");
      }

		// Wait some time
		time::msleep( 100 );
	}

   return 0;
}

