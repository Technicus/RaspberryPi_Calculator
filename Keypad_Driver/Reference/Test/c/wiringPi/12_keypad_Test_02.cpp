
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
   
   unsigned char keyPadChar[4][3] = {
      {'1', '2', '3'},
      {'4', '5', '6'},
      {'7', '8', '9'},
      {'#', '0', '*'}
   };
   
   unsigned int keyPadBool[4][3] = {
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0}
   };
   
   int column[3] = {26, 21, 22};
   
   int row[4] = {16, 17, 18, 19};
   
   int columnTest = 0;
   int columnCount = 0;
   int rowTest = 0;
   int rowCount = 0;
      
   int keyPress = 0;
   int keyToggle = 0;
   int numberOfPresses = 0;
   
   while ((keyPress == 0 and rowTest == 0)) // While no key pressed
   {
      for ( columnCount = 0; columnCount <= 2;  )
      {
         digitalWrite (column[columnCount], HIGH);
         
         for ( rowCount = 0; rowCount <= 3;  )
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
      //getkeypad();
      keyPressed = getkeypad();
      std::cout << "Button press = " << keyPressed << "\n";
      delay(180);
   
   
   
   
   }
   return 0 ;
}
        




