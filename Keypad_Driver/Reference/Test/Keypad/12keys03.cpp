/* 
    Title --- 12keys1.cpp [examples]

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
    ( 21, 22, 23*)     colums = 3
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
    (16, 17, 18, 19)  rows = 4
*/

// Define the keymap
std::vector< uint8_t > keymap = {
   
   '1', '2', '3',
   '4', '5', '6',
   '7', '8', '9',
   '*', '0', '#'
};

// Matrix keypad controller
keypad::matrix dev( { 26, 21, 22 }, { 16, 17, 18, 19 }, keymap );

int main( int argc, char *args[] ) {

   for ( ;; ) {
      
      // Check the button state
      if ( dev.keyPressed('1') )
         std::cout << "key '1'\n";
      if ( dev.keyPressed('2') )
         std::cout << "key '2'\n";
      if ( dev.keyPressed('3') )
         std::cout << "key '3'\n";
      if ( dev.keyPressed('4') )
         std::cout << "key '4'\n";
      if ( dev.keyPressed('5') )
         std::cout << "key '5'\n";
      if ( dev.keyPressed('6') )
         std::cout << "key '6'\n";
      if ( dev.keyPressed('7') )
         std::cout << "key '7'\n";
      if ( dev.keyPressed('8') )
         std::cout << "key '8'\n";
      if ( dev.keyPressed('9') )
         std::cout << "key '9'\n";
      if ( dev.keyPressed('*') )
         std::cout << "key '*'\n";
      if ( dev.keyPressed('0') ){
         //std::cout << "key '0'\n";
         std::cout << "You have pressed buttons 0\n . . . keypad shutdown ?. . .\n";
         std::cout << "Press 0 to confirm shutdown or a different button to abort shutdown . . .\n";
         if ( dev.keyPressed('0') )
            system ("sudo shutdown -h now");
         }
      if ( dev.keyPressed('#') )
         std::cout << "key '#'\n";

      
/*      if ( dev.pressed('0') && dev.pressed('1') ){
         std::cout << "You have pressed buttons 0 and 2!\n . . . keypad shutdown . . .\n";
         system ("sudo shutdown -h now");
      }
      
      if ( dev.pressed('0') && dev.pressed('3') ){
         std::cout << "You have pressed buttons 9 and 11!\n . . . keypad rebooting . . .\n";
         system ("sudo reboot");
      }
 */     
      // Wait some time
      time::msleep( 100 );
   }
   
	return 0;
}

/*


if ( dev.pressed('1') && dev.pressed('3') )
   std::cout << "You have pressed buttons 1 and 4!\n";

if ( dev.pressed('0') && dev.pressed('1') ){
   std::cout << "You have pressed buttons 0 and 2!\n . . . keypad shutdown . . .\n";
   system ("sudo shutdown -h now");
   }
   
   if ( dev.pressed('0') && dev.pressed('3') ){
      std::cout << "You have pressed buttons 9 and 11!\n . . . keypad rebooting . . .\n";
      system ("sudo reboot");
      }


switch ( a ) {
   case b:
      // Code
      break;
   case c:
      // Code
      break;
   default:
      // Code
      break;
      }

*/
