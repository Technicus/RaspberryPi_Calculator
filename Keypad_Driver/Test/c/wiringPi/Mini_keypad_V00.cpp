
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
   
   unsigned int keyPadBool[4][3] = {
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0}
   };
   
   int column[2] = {2, 3};
   
   int row[2] = {14, 5};
   
   int columnTest = 0;
   int columnCount = 0;
   int rowTest = 0;
   int rowCount = 0;
      
   int keyPress = 0;
   int keyToggle = 0;
   int numberOfPresses = 0;
   
   while ((keyPress == 0 and rowTest == 0)) // While no key pressed
   {
      for ( columnCount = 0; columnCount <= 1;  )
      {
         digitalWrite (column[columnCount], HIGH);
         
         for ( rowCount = 0; rowCount <= 1;  )
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
   
   wiringPiSetup ();
                                  
   pinMode (2, OUTPUT);            // column 1                    
   pinMode (3, OUTPUT);            // column 2                                         
                                  
   pinMode (14, INPUT);             // row 1
   pinMode (5, INPUT);             // row 2
   
   pullUpDnControl (14, PUD_DOWN);  // row 1
   pullUpDnControl (5, PUD_DOWN);  // row 2
   
   for (;;)
   {
      //getkeypad();
      keyPressed = getkeypad();
      std::cout << "Button press = " << keyPressed << "\n";
      delay(180);
   
   
   
   
   }
   return 0 ;
}
        




