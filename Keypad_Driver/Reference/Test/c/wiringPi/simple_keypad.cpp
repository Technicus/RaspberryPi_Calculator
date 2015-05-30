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
      {13, 14, 15, 16,  0, 18},
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
   
}    
    
int main (void)
{
   std::cout << "Starting . . .\n";
   
   int keyPressed = 0;
   int keyPress = 0;
   int keyToggle = 0;
   int numberOfPresses = 0;
   unsigned char KeyPressed;
   
//    key_init();
//    wiringPiSetup ();
   wiringPiSetupGpio ();
   pinMode (col0, OUTPUT); 
   pinMode (col1, OUTPUT); 
   pinMode (col2, OUTPUT); 
   pinMode (col3, OUTPUT); 
   pinMode (col4, OUTPUT); 
   pinMode (col5, OUTPUT);// column 4    
   
   digitalWrite (col0, LOW);
   digitalWrite (col1, HIGH);
   digitalWrite (col2, LOW);
   digitalWrite (col3, LOW);
   digitalWrite (col4, LOW);
   digitalWrite (col5, LOW);
   
   pinMode (row1, INPUT);            // column 4    
   
   pullUpDnControl (row1, PUD_DOWN);  // row 1
   
   for (;;)
   {
      std::cout << "\tLooping . . .\n";
      std::cout << "\t\tReading . . .\n";
      keyPressed = digitalRead (row1);
     // keyPressed = get_key();
      if(keyPressed == 0)
      {
//          std::cout << "\t\tReading . . .\n";
         std::cout << "\t\t\t `digitalRead (row1)` =  0, " << keyPressed << "\n";
      }
      else
      {
         std::cout << "\t\t\t `digitalRead (row1)` =  1, " << keyPressed << "\n";
         //std::cout << "\t\t\tButton pressed, `digitalRead (row1)` = " << keyPressed << "\n";
         
      }
      
      delay(180);
      
   }
   return 0 ;
}   