
#include <iostream>
#include <stdlib.h>
#include <wiringPi.h>                              // |WiringPi library

// digitalRead (16);                                  // |This function returns the value read at the given pin. It will 
// digitalRead (17);                                  // |be HIGH or LOW (1 or 0) depending on the logic level at the pin.
// digitalRead (18);
// digitalRead (19);

//
// This function gets a key from the keypad and returns it to calling program
//
unsigned char getkeypad()
{
   unsigned char key = 0;
   
   unsigned char keyPadChar[10][6] = {
      {'1', '2', '3', '4', '5', '6'},
      {'7', '8', '9', '0', 'A', 'B'},
      {'C', 'D', 'E', 'F', 'G', 'H'},
      {'I', 'J', 'K', 'L', 'M', 'N'},
      {'O', 'P', 'Q', 'R', 'S', 'T'},
      {'U', 'V', 'W', 'X', 'Y', 'Z'},
      {'1', '2', '3', '4', '5', '6'},
      {'1', '2', '3', '4', '5', '6'},
      {'1', '2', '3', '4', '5', '6'},
      {'1', '2', '3', '4', '5', '6'}
   };
   
   unsigned int keyPadBool[10][6] = {
      {'0', '0', '0', '0', '0', '0'},
      {'0', '0', '0', '0', '0', '0'},
      {'0', '0', '0', '0', '0', '0'},
      {'0', '0', '0', '0', '0', '0'},
      {'0', '0', '0', '0', '0', '0'},
      {'0', '0', '0', '0', '0', '0'},
      {'0', '0', '0', '0', '0', '0'},
      {'0', '0', '0', '0', '0', '0'},
      {'0', '0', '0', '0', '0', '0'},
      {'0', '0', '0', '0', '0', '0'}
   };
   
   column[6] = {2, 3, 4, 17, 27, 22};
   
   row[10] = {14, 5, 6, 13, 19, 28, 12, 16, 20, 21};
   
   int columnTest = 0;
   int columnCount = 0;
   int rowTest = 0;
   int rowCount = 0;
      
   int keyPress = 0;
   int keyToggle = 0;
   int numberOfPresses = 0;
   
   while ((keyPress == 0 and rowTest == 0)) // While no key pressed
   {
      for ( columnCount = 0; columnCount <= 5;  )
      {
         digitalWrite (column[columnCount], HIGH);
         
         for ( rowCount = 0; rowCount <= 9;  )
         {
            keyPress = digitalRead (row[rowCount]);
            
            if(keyPress == 1)
            {
               rowTest = 1;
               key = keyPadChar[rowCount][columnCount];
//                std::cout << "Button press = " << key << "\n";
//                delay(20);
            }
            
            rowCount++;
         }
         
         digitalWrite (column[columnCount], LOW);
         columnCount++;
      }
   }
   
   //return (0);                         
   return (key);  // Return key number
}

int main (void)
{
   char keyPressed = 0;
   int keyPress = 0;
   int keyToggle = 0;
   int numberOfPresses = 0;
   unsigned char KeyPressed;
   int columns[6] = {2, 3, 4, 17, 27, 22};
   int rows[10] = {14, 5, 6, 13, 19, 28, 12, 16, 20, 21};
   
   wiringPiSetup ();
                                  
   pinMode (2, OUTPUT);            // column 0 - set as output                    
   pinMode (3, OUTPUT);            // column 1 - set as output                                         
   pinMode (4, OUTPUT);            // column 2 - set as output
   pinMode (17, OUTPUT);            // column 3 - set as output                    
   pinMode (27, OUTPUT);            // column 4 - set as output                                         
   pinMode (22, OUTPUT);            // column 5 - set as output   
   
   pinMode (14, INPUT);             // row 0 - set as input
   pinMode (5, INPUT);             // row 1 - set as input
   pinMode (6, INPUT);             // row 2 - set as input
   pinMode (13, INPUT);             // row 3 - set as input
   pinMode (19, INPUT);             // row 4 - set as input
   pinMode (28, INPUT);             // row 5 - set as input
   pinMode (12, INPUT);             // row 6 - set as input
   pinMode (16, INPUT);             // row 7 - set as input
   pinMode (20, INPUT);             // row 8 - set as input
   pinMode (21, INPUT);             // row 9 - set as input
   
   pullUpDnControl (, PUD_DOWN);  // row 0 - set internal pulldown
   pullUpDnControl (, PUD_DOWN);  // row 1 - set internal pulldown
   pullUpDnControl (, PUD_DOWN);  // row 2 - set internal pulldown
   pullUpDnControl (, PUD_DOWN);  // row 3 - set internal pulldown
   pullUpDnControl (, PUD_DOWN);  // row 4 - set internal pulldown
   pullUpDnControl (, PUD_DOWN);  // row 5 - set internal pulldown
   pullUpDnControl (, PUD_DOWN);  // row 6 - set internal pulldown
   pullUpDnControl (, PUD_DOWN);  // row 4 - set internal pulldown
   pullUpDnControl (, PUD_DOWN);  // row 8 - set internal pulldown
   pullUpDnControl (, PUD_DOWN);  // row 9 - set internal pulldown
   
   for (;;)
   {
      //getkeypad();
      keyPressed = getkeypad();
      std::cout << "Button press = " << keyPressed << "\n";
      delay(180);
   
   
   
   
   }
   return 0 ;
}
        




