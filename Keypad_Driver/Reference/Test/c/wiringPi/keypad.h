/*#include <avr/io.h>
 *	// Include file for AVR
 * # *define keyport PORTA		//Keypad Port
 * #define keyportddr DDRA		//Data Direction Register
 * #define keyportpin PINA		//Keypad Port Pins
 */

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
   wiringPiSetup ();
   
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
   unsigned char i,key=1;
   for(i=0;i<5;i++){		//Loop for 6 cols
      keyport &=~(0x80>> i);	//Make rows low one by one
      if(!(keyportpin & (1<<col1))){
         //check COL1
         while(!(keyportpin & (1<<col1)));
         //wait for release
         return key;
         //return pressed key value
      }
      if(!(keyportpin & (1<<col2))){
         //Check COL2
         key += 1;
         //Second key pressed
         while(!(keyportpin & (1<<col2)));
         //wait for release
         return key;
         //return key value
      }
      if(!(keyportpin & (1<<col3))){
         //Check COL3
         key += 2;
         //Third key pressed
         while(!(keyportpin & (1<<col3)));
         //Wait for release
         return key;
         //Return value
      }
      if(!(keyportpin & (1<<col4))){
         //check COL4
         key += 3;
         //Fourth key pressed
         while(!(keyportpin & (1<<col4)));
         //Wait for release
         return key;
         //Return key value
      }
      key +=4;	//Next row
      keyport |= 0x80>
      >
      i;
      //make read row high again
   }
   return FALSE;	//return false if no key pressed
}    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    