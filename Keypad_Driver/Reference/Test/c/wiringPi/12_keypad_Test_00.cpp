
#include <iostream>
#include <stdlib.h>
#include <wiringPi.h>                              // |WiringPi library

// wiringPiSetupGpio ();                              /* |This initialises the wiringPi system and assumes that the 
//                                                       |calling program is going to be using the Broadcom GPIO pin numbers directly 
//                                                       |with no re-mapping. This function needs to be called with root privileges. 
//                                                    */
// 
// pinMode (26, OUTPUT);                              // |This sets the mode of a pin to either INPUT, OUTPUT, or PWM_OUTPUT. 
// pinMode (22, OUTPUT);                              // |Note that only wiringPi pin 1 (BCM_GPIO 18) supports PWM output. 
// pinMode (23, OUTPUT);                              // |The pin number is the number obtained from the pins table.
// pinMode (16, INPUT);                               // |This function has no effect when in Sys mode
// pinMode (17, INPUT);
// pinMode (18, INPUT);
// pinMode (19, INPUT);
// 
// pullUpDnControl (16, PUD_DOWN);                    // |This sets the pull-up or pull-down resistor mode on the given pin, 
// pullUpDnControl (17, PUD_DOWN);                    // |which should be set as an input. Unlike the Arduino, the BCM2835 
// pullUpDnControl (18, PUD_DOWN);                    // |has both pull-up an down internal resistors. The parameter pud 
// pullUpDnControl (19, PUD_DOWN);                    // |should be; PUD_OFF, (no pull up/down), PUD_DOWN (pull to ground) 
//                                                    // |or PUD_UP (pull to 3.3v)
//                                                    // |This function has no effect when in Sys mode. If you need to 
//                                                    // |activate a pull-up/pull-down, then you can do it with the gpio 
//                                                    // |program in a script before you start your program.
// 
// digitalWrite (26, HIGH);                           // |Writes the value HIGH or LOW (1 or 0) to the given pin which must
// digitalWrite (22, LOW);                            // |have been previously set as an output.
// digitalWrite (23, LOW);   
// 
// digitalRead (16);                                  // |This function returns the value read at the given pin. It will 
// digitalRead (17);                                  // |be HIGH or LOW (1 or 0) depending on the logic level at the pin.
// digitalRead (18);
// digitalRead (19);


int main (void)
{
   int keyPress = 0;
   int keyToggle = 0;
   int numberOfPresses = 0;
   
   wiringPiSetup ();
   
   pinMode (26, OUTPUT);                              
   pinMode (21, OUTPUT);                              
   pinMode (22, OUTPUT);
   
   digitalWrite (26, HIGH);
   digitalWrite (21, HIGH);
   digitalWrite (22, HIGH);
   
   pinMode (16, INPUT);
   pinMode (17, INPUT);
   pinMode (18, INPUT);
   pinMode (19, INPUT);
   
   pullUpDnControl (16, PUD_DOWN);
   pullUpDnControl (17, PUD_DOWN);
   pullUpDnControl (18, PUD_DOWN);
   pullUpDnControl (19, PUD_DOWN);
   
   for (;;)
   {
      keyPress = digitalRead (16);
      delay (100);
      if ( keyPress == 1 )
         keyToggle = 1;
      if ( keyPress == 1 and keyToggle == 1){
         keyToggle = 0;
         numberOfPresses++;
         std::cout << "Button press " << numberOfPresses << "\n";
      }
      keyPress = digitalRead (17);
      delay (100);
      if ( keyPress == 1 )
         keyToggle = 1;
      if ( keyPress == 1 and keyToggle == 1){
         keyToggle = 0;
         numberOfPresses++;
         std::cout << "Button press " << numberOfPresses << "\n";
      }
      keyPress = digitalRead (18);
      delay (100);
      if ( keyPress == 1 )
         keyToggle = 1;
      if ( keyPress == 1 and keyToggle == 1){
         keyToggle = 0;
         numberOfPresses++;
         std::cout << "Button press " << numberOfPresses << "\n";
      }
      keyPress = digitalRead (19);
      delay (100);
      if ( keyPress == 1 )
         keyToggle = 1;
      if ( keyPress == 1 and keyToggle == 1){
         keyToggle = 0;
         numberOfPresses++;
         std::cout << "Button press " << numberOfPresses << "\n";
      }
   }
   return 0 ;
}
        




