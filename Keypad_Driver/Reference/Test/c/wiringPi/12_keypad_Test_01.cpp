
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
   unsigned char i, Key = 0;
   
   unsigned char keyPadChar[3][4] = {
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9},
      {'#', 0, '*'}
   };
   
   unsigned int keyPadBool[3][4] = {
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0}
   };
   
   int column[3] = {  
      {26, 21, 22} 
   };
   
   int row[4] = {  
      {16, 17, 18, 19} 
   };
   
   int columnTest = 0;
   int columnCount = 0;
   int rowTest = 0;
   int rowCount = 0;
      
   int keyPress = 0;
   int keyToggle = 0;
   int numberOfPresses = 0;
   
   
   while ((keyPress and rowTest == 0) // While no key pressed
   {
      digitalWrite (column[columnCount], HIGH);         // column 1                    
      
      for ( x = 0; x < 3; x++ ) {
         keyPress = digitalRead (row[rowCount]);
         if(KeyPress == 1)
         {
            keyPadTestBool[columnCount][rowCount] = 1;
            Key = keyPadChar[columnCount][rowCount];
            std::cout << "Button press " << key << "\n";
         }
         rowCount++; // row number
         x++;
      }
      
      if(rowCount == 3)
      {
         rowCount = 0; // Back to row 1
      }
      rowCount++;
   }
   Delay_Ms(20);                        			// Switch debounce
     
   return (Key);                          			// Return key number
}

int main (void)
{
   int keyPress = 0;
   int keyToggle = 0;
   int numberOfPresses = 0;
   unsigned char KeyPressed;
   
   wiringPiSetup ();
                                  
   pinMode (26, OUTPUT);            // column 1                    
   pinMode (21, OUTPUT);            // column 2                                         
   pinMode (22, OUTPUT);            // column 3                    
                                  
   pinMode (16, INPUT);             // row 1
   pinMode (17, INPUT);             // row 2
   pinMode (18, INPUT);             // row 3
   pinMode (19, INPUT);             // row 4
   
   pullUpDnControl (16, PUD_DOWN);  // row 1
   pullUpDnControl (17, PUD_DOWN);  // row 2
   pullUpDnControl (18, PUD_DOWN);  // row 3
   pullUpDnControl (19, PUD_DOWN);  // row 4
   
   for (;;)
   {
      keyPressed = getkeypad();
   
   
   
   
   }
   return 0 ;
}
        




