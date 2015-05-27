#include <avr/io.h>
// Include file for AVR
#define keyport PORTA		//Keypad Port
#define keyportddr DDRA		//Data Direction Register
#define keyportpin PINA		//Keypad Port Pins

#define col1 PA0		//Column1 PortA.0
#define col2 PA1		//Column2 PortA.1
#define col3 PA2		//Column3 PortA.2
#define col4 PA3		//Column4 PortA.3

#define TRUE 1
#define FALSE 0

unsigned char keyval;	//A variable

/*
 + *---------------------------------------+
 | Prototype: void key_init(void);       |
 | Return Type: void                     |
 | Arguments: None                       |
 | Description: Initialize ports and     |
 |              Keypad.                  |
 +---------------------------------------+
 */
void key_init(){
   keyportddr = 0xF0;
   keyport = 0x0F;
}

/*
 + *-----------------------------------------------+
 | Prototype: unsigned char get_key(void);       |
 | Return Type: unsigned char                    |
 | Arguments: None                               |
 | Description: To read key from the keypad      |
 +-----------------------------------------------+
 */
unsigned char get_key(){
   unsigned char i,key=1;
   for(i=0;i<4;i++){		//Loop for 4 rows
      keyport &=~(0x80>>i);	//Make rows low one by one
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