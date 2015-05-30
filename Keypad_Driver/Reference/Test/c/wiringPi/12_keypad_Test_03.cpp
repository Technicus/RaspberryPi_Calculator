
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
   
   unsigned int keyPadChar[10][6] = {
      {'0', '1', '2', '3', '4', '5'},
      {'6', '7', '8', '9', '10', '11'},
      {'12', '13', '14', '15', 'R', '16'},
      {'17', '18', '19', '20', '21', '22'}
      {'23', '24', '25', '26', '27', '28'},
      {'29', '30', '31', '32', '33', '34'},
      {'35', '36', '37', '38', '39', '40'},
      {'41', '42', '43', '44', '45', '46'},
      {'47', '48', '49', '50', '51', '52'},
      {'53', '54', '55', '56', '57', '58'}
   };
   
   unsigned char keyPadColumn[6] = {
      {'A', 'B', 'C', 'D', 'E', 'F'}
   };     
   unsigned char keyPadRow[10] = {
      {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}
   };
   
   unsigned int keyPadBool[10][6] = {
      {'0', '0', '0', '0', '0', '0',},
      {'0', '0', '0', '0', '0', '0',},
      {'0', '0', '0', '0', '0', '0',},
      {'0', '0', '0', '0', '0', '0',},
      {'0', '0', '0', '0', '0', '0',},
      {'0', '0', '0', '0', '0', '0',},
      {'0', '0', '0', '0', '0', '0',},
      {'0', '0', '0', '0', '0', '0',},
      {'0', '0', '0', '0', '0', '0',},
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
        




