
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
   
   byte keyboard keyPadChar[10][6] = {
      {'A0', 'B0', 'C0', 'D0', 'E0', 'F0'},
      {'A1', 'B1', 'C1', 'D1', 'E1', 'F1'},
      {'A2', 'B3', 'C3', 'D3', 'DR', 'F3'},
      {'A3', 'B3', 'C3', 'D3', 'E3', 'F3'}
      {'A4', 'B4', 'C4', 'D4', 'E4', 'F4'},
      {'A5', 'B5', 'C5', 'D5', 'E5', 'F5'},
      {'A6', 'B6', 'C6', 'D6', 'E6', 'F6'},
      {'A7', 'B7', 'C7', 'D7', 'E7', 'F7'},
      {'A8', 'B8', 'C8', 'D8', 'E8', 'F8'},
      {'A9', 'B9', 'C9', 'D9', 'E9', 'F9'}
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
   
   int column[6] = {2, 3, 4, 17, 27, 22};
   
   int row[10] = {14, 5, 6, 13, 19, 28, 12, 18, 20, 21};
   
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
   
   wiringPiSetup ();
                                  
   pinMode (column[0], OUTPUT);            // column 0 - set as output                    
   pinMode (column[1], OUTPUT);            // column 1 - set as output                                         
   pinMode (column[2], OUTPUT);            // column 2 - set as output
   pinMode (column[3], OUTPUT);            // column 3 - set as output                    
   pinMode (column[4], OUTPUT);            // column 4 - set as output                                         
   pinMode (column[5], OUTPUT);            // column 5 - set as output   
                                  
   pinMode (row[0], INPUT);             // row 0 - set as input
   pinMode (row[1], INPUT);             // row 1 - set as input
   pinMode (row[2], INPUT);             // row 2 - set as input
   pinMode (row[3], INPUT);             // row 3 - set as input
   pinMode (row[4], INPUT);             // row 4 - set as input
   pinMode (row[5], INPUT);             // row 5 - set as input
   pinMode (row[6], INPUT);             // row 6 - set as input
   pinMode (row[7], INPUT);             // row 7 - set as input
   pinMode (row[8], INPUT);             // row 8 - set as input
   pinMode (row[9], INPUT);             // row 9 - set as input
   
   pullUpDnControl (row[0], PUD_DOWN);  // row 0 - set internal pulldown
   pullUpDnControl (row[1], PUD_DOWN);  // row 1 - set internal pulldown
   pullUpDnControl (row[2], PUD_DOWN);  // row 2 - set internal pulldown
   pullUpDnControl (row[3], PUD_DOWN);  // row 3 - set internal pulldown
   pullUpDnControl (row[4], PUD_DOWN);  // row 4 - set internal pulldown
   pullUpDnControl (row[5], PUD_DOWN);  // row 5 - set internal pulldown
   pullUpDnControl (row[6], PUD_DOWN);  // row 6 - set internal pulldown
   pullUpDnControl (row[7], PUD_DOWN);  // row 4 - set internal pulldown
   pullUpDnControl (row[8], PUD_DOWN);  // row 8 - set internal pulldown
   pullUpDnControl (row[9], PUD_DOWN);  // row 9 - set internal pulldown
   
   for (;;)
   {
      //getkeypad();
      keyPressed = getkeypad();
      std::cout << "Button press = " << keyPressed << "\n";
      delay(180);
   
   
   
   
   }
   return 0 ;
}
        




