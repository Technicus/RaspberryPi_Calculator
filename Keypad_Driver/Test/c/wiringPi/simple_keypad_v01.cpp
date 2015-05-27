/*#include <avr/io.h>
 *	// Include file for AVR
 * # *define keyport PORTA		//Keypad Port
 * #define keyportddr DDRA		//Data Direction Register
 * #define keyportpin PINA		//Keypad Port Pins
 */


#include <iostream>
#include <stdlib.h>
#include <wiringPi.h> 

#define col0 2
#define col1 3
#define col2 4
#define col3 17
#define col4 27
#define col5 22

#define row0 14
#define row1 5
#define row2 6
#define row3 13
#define row4 19
#define row5 26
#define row6 12
#define row7 16
#define row8 20
#define row9 21

#define TRUE 1
#define FALSE 0

unsigned char keyval;	//A variable

/*
 * + *---------------------------------------+
 * | Prototype: void key_init(void);       |
 * | Return Type: void                     |
 * | Arguments: None                       |
 * | Description: Initialize ports and     |
 * |              Keypad.                  |
 * +---------------------------------------+
 */
void key_init(){
   wiringPiSetupGpio ();
   
   pinMode (col0, OUTPUT);            // column 0                    
   pinMode (col1, OUTPUT);            // column 1                                         
   pinMode (col2, OUTPUT);            // column 2        
   pinMode (col3, OUTPUT);            // column 3                    
   pinMode (col4, OUTPUT);            // column 4                                         
   pinMode (col5, OUTPUT);            // column 5         
   
   digitalWrite (col0, LOW);
   digitalWrite (col1, LOW);
   digitalWrite (col2, LOW);
   digitalWrite (col3, LOW);
   digitalWrite (col4, LOW);
   digitalWrite (col5, LOW);
   
   pinMode (row0, INPUT);             // row 1
   pinMode (row1, INPUT);             // row 2
   pinMode (row2, INPUT);             // row 3
   pinMode (row3, INPUT);             // row 4
   pinMode (row4, INPUT);             // row 1
   pinMode (row5, INPUT);             // row 2
   pinMode (row6, INPUT);             // row 3
   pinMode (row7, INPUT);             // row 4
   pinMode (row8, INPUT);             // row 4
   pinMode (row9, INPUT);             // row 4
   
   pullUpDnControl (row0, PUD_DOWN);  // row 1
   pullUpDnControl (row1, PUD_DOWN);  // row 1
   pullUpDnControl (row2, PUD_DOWN);  // row 1
   pullUpDnControl (row3, PUD_DOWN);  // row 1
   pullUpDnControl (row4, PUD_DOWN);  // row 1
   pullUpDnControl (row5, PUD_DOWN);  // row 1
   pullUpDnControl (row6, PUD_DOWN);  // row 1
   pullUpDnControl (row7, PUD_DOWN);  // row 2
   pullUpDnControl (row8, PUD_DOWN);  // row 3
   pullUpDnControl (row9, PUD_DOWN);  // row 4
}

/*
 * + *-----------------------------------------------+
 * | Prototype: unsigned char get_key(void);       |
 * | Return Type: unsigned char                    |
 * | Arguments: None                               |
 * | Description: To read key from the keypad      |
 * +-----------------------------------------------+
 */
unsigned char get_key(){
//    if(!(keyportpin & (1<<col1))){
//       //check COL1
//       while(!(keyportpin & (1<<col1)));
//       //wait for release
//       return key;
//       //return pressed key value
   unsigned int keyPadNumber[10][6] = {
      {1,   2,  3,  4,  5,  6},
      {7,   8,  9, 10, 11, 12},
      {13, 14, 15, 16, 17, 18},
      {19, 20, 21, 22, 23, 24}, 
      {25, 26, 27, 28, 29, 30},
      {31, 32, 33, 34, 35, 36},
      {37, 38, 39, 40, 41, 42},
      {43, 44, 45, 46, 47, 48},
      {49, 50, 51, 52, 53, 54},
      {55, 56, 57, 58, 59, 60}
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
   
   int column[6] = {col0, col1, col2, col3, col4, col5};
   
   int row[10] = {row0, row1, row2, row3, row4, row5, row6, row7, row8, row9};
   
   int columnTest = 0;
   int columnCount = 0;
   int rowTest = 0;
   int rowCount = 0;
   
   int key = 0;
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
               key = keyPadNumber[rowCount][columnCount];
               std::cout << "Button press in function = " << key << "\n";
               //delay(20);
               //return (key);
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
  
   std::cout << "Starting . . .\n";
   key_init();
   
//    int keyPressed = 0;
//    int keyPress = 0;
//    int keyToggle = 0;
//    int numberOfPresses = 0;
//    unsigned char KeyPressed;
   
   
   for (;;)
   {
      //keyPressed = getkeypad();
      std::cout << "Button press = " << get_key() << "\n";
      delay(180);
   }
   return 0 ;
}