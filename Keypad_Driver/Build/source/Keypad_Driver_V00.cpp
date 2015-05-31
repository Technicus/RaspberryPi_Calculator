/*#include <avr/io.h>
 *	// Include file for AVR
 * # *define keyport PORTA		//Keypad Port
 * #define keyportddr DDRA		//Data Direction Register
 * #define keyportpin PINA		//Keypad Port Pins
 */


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <sys/stat.h>

#define die(str, args...) do { \
perror(str); \
exit(EXIT_FAILURE); \
} while(0)

#define col0 22
#define col1 27
#define col2 17
#define col3 4
#define col4 3
#define col5 2

#define row0 5
#define row1 6
#define row2 13
#define row3 19
#define row4 26
#define row5 21
#define row6 20
#define row7 16
#define row8 12
#define row9 23

#define up 18
#define down 15
#define left 14

#define TRUE 1
#define FALSE 0

unsigned char keyval;	//A variable

/*
 * + *---------------------------------------+
 * | Prototype: void key_init(void);       |
 * | Return Type: void                     |
 * | Arguments: None                       |
 * | Description: Initialize pins and      |
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
                                                                                                
   pullUpDnControl (up, PUD_DOWN);    // Directional Switch Up                                
   pullUpDnControl (down, PUD_DOWN);  // Directional Switch Down                               
   pullUpDnControl (left, PUD_DOWN);  // Directional Switch Left
}

/*
 * + *-----------------------------------------------+
 * | Prototype: unsigned int get_key(void);        |
 * | Return Type: unsigned int                     |
 * | Arguments: None                               |
 * | Description: To read key from the keypad      |
 * +-----------------------------------------------+
 */
unsigned int get_key(){
   
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
      for ( columnCount = 0; columnCount <= 5; columnCount++  )
      {
         digitalWrite (column[columnCount], HIGH);
         for ( rowCount = 0; rowCount <= 9; rowCount++ )
         {
            keyPress = digitalRead (row[rowCount]);
            
            if(keyPress == 1)
            {
               rowTest = 1;
               key = keyPadNumber[rowCount][columnCount];
               keyPadBool[rowCount][columnCount] = 1;
               if(keyPadBool[0][0] and keyPadBool[9][0] == 1)
               {
                  std::cout << "\t\t\tKey combination 1 and 55 -- SHUTDOWN . . .\n";
                  delay(180);
                  //system("shutdown -P -t 0 -h");
                  system("halt");
               }
               if(keyPadBool[0][0] and keyPadBool[9][5] == 1)
               {
                  std::cout << "\t\t\tKey combination 1 and 60 -- REBOOT . . .\n";
                  delay(180);
                  system("shutdown -r now");
               }
               if(keyPadBool[0][0] and keyPadBool[0][5] == 1)
               {
                  std::cout << "\t\t\tKey combination 1 and 6 -- UPDATE . . .\n";
                  delay(180);
                  system("/home/pi/Calculator/Development/Build/Keypad_Kernel_Driver/compile_v01.sh ");
               }
               if(keyPadBool[0][0] and keyPadBool[9][2] == 1)
               {
                  std::cout << "\t\t\tKey combination 1 and 58 -- ROTATE 90 . . .\n";
                  delay(180);
                  char c;
                  int in, out;
                  in = open("/boot/config.txt.tft-90", O_RDONLY);
                  out = open("/boot/config.txt", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
                  while(read(in,&c,1) == 1)
                     write(out,&c,1);
                  
                  system("shutdown -r now");
               }
               if(keyPadBool[0][0] and keyPadBool[9][1] == 1)
               {
                  std::cout << "\t\t\tKey combination 1 and 58 -- ROTATE 0 . . .\n";
                  char c;
                  int in, out;
                  in = open("/boot/config.txt.tft-0", O_RDONLY);
                  out = open("/boot/config.txt", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
                  while(read(in,&c,1) == 1)
                     write(out,&c,1);
                  system("shutdown -r now");
               }
               if(keyPadBool[0][0] and keyPadBool[9][3] == 1)
               {
                  std::cout << "\t\t\tKey combination 1 and 58 -- ROTATE 90 . . .\n";
                  delay(180);
                  char c;
                  int in, out;
                  in = open("/boot/config.txt.tft-180", O_RDONLY);
                  out = open("/boot/config.txt", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
                  while(read(in,&c,1) == 1)
                     write(out,&c,1);
                  
                  system("shutdown -r now");
               }
               if(keyPadBool[0][0] and keyPadBool[9][4] == 1)
               {
                  std::cout << "\t\t\tKey combination 1 and 58 -- ROTATE 0 . . .\n";
                  char c;
                  int in, out;
                  in = open("/boot/config.txt.tft-270", O_RDONLY);
                  out = open("/boot/config.txt", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
                  while(read(in,&c,1) == 1)
                     write(out,&c,1);
                  system("shutdown -r now");
               }
            }
            else
            {
               keyPadBool[rowCount][columnCount] = 0;
            }
         }
         digitalWrite (column[columnCount], LOW);
      }
   }
   return (key);  // Return key number
}    
    
int send_event(int fd, __u16 type, __u16 code, __s32 value)
{
   struct input_event event;
   
   memset(&event, 0, sizeof(event));
   event.type = type;
   event.code = code;
   event.value = value;
   
   if (write(fd, &event, sizeof(event)) != sizeof(event)) {
      fprintf(stderr, "\t\t\tError on send_event\n");
      return -1;
   }
   
   return 0;
}

int main(int argc, char *argv[])
{
//    const char *KEY_CODE[2];
//    KEY_CODE[0] = "KEY_A";
//    KEY_CODE[1] = "KEY_B";
   
   //std::cout << "Starting . . .\n";
   //std::cout << "\tSetup uinput . . .\n";
   int key;
   int                    fd;
   struct uinput_user_dev uidev;
   struct input_event     ev;
   int                    dx, dy;
   int                    i;
   
   struct uinput_user_dev device;
   memset(&device, 0, sizeof device);
   
   fd=open("/dev/uinput",O_WRONLY);
   //fd=open("/dev/input/uinput",O_WRONLY);
   strcpy(device.name,"keypad_driver_60");
   
   device.id.bustype=BUS_USB;
   device.id.vendor=1;
   device.id.product=1;
   device.id.version=1;
   
   for (i=0; i < ABS_MAX; i++) {
      device.absmax[i] = -1;
      device.absmin[i] = -1;
      device.absfuzz[i] = -1;
      device.absflat[i] = -1;
   }
   
   device.absmin[ABS_X]=0;
   device.absmax[ABS_X]=255;
   device.absfuzz[ABS_X]=0;
   device.absflat[ABS_X]=0;
   
   if (write(fd,&device,sizeof(device)) != sizeof(device))
   {
      fprintf(stderr, "\t\terror setup\n");
   }   
   
   if (ioctl(fd,UI_SET_EVBIT,EV_KEY) < 0)
      fprintf(stderr, "\t\terror evbit key\n");
   
   if (ioctl(fd,UI_SET_KEYBIT, KEY_A) < 0)
      fprintf(stderr, "\t\terror evbit key\n");
   
   if (ioctl(fd,UI_SET_EVBIT,EV_REL) < 0)
      fprintf(stderr, "\t\terror evbit rel\n");
   
   for(i=REL_X;i<REL_MAX;i++)
      if (ioctl(fd,UI_SET_RELBIT,i) < 0)
         fprintf(stderr, "\t\terror setrelbit %d\n", i);
      
      if (ioctl(fd,UI_DEV_CREATE) < 0)
      {
         fprintf(stderr, "\t\terror create\n");
      }
      
   //std::cout << "\tSetup uinput complete . . .\n";
   
   
   key_init();
   
   int returnKeyPress = 0;
   
   for (;;)
   {
      returnKeyPress = get_key();
     // std::cout << "\t\tButton press = " << returnKeyPress << "\n";
      
      if (returnKeyPress == 1) {
        // std::cout << "\t\t\tattempting to send to uinput . . .\n";

         
         send_event(fd, EV_KEY, KEY_A, 1);
         send_event(fd, EV_SYN, SYN_REPORT, 0);
         delay(180);
         send_event(fd, EV_KEY, KEY_A, 0);
         send_event(fd, EV_SYN, SYN_REPORT, 0);
      }
      if (returnKeyPress == 2) {
         std::cout << "\t\t\tattempting to send to uinput . . . Button press = " << returnKeyPress << "\n";
         if (ioctl(fd,UI_SET_EVBIT,EV_KEY) < 0)
            fprintf(stderr, "\t\terror evbit key\n");
         
         if (ioctl(fd,UI_SET_KEYBIT, KEY_B) < 0)
            fprintf(stderr, "\t\terror evbit key\n");
         
         if (ioctl(fd,UI_SET_EVBIT,EV_REL) < 0)
            fprintf(stderr, "\t\terror evbit rel\n");
         
         send_event(fd, EV_KEY, KEY_B, 1);
         send_event(fd, EV_SYN, SYN_REPORT, 0);
         delay(180);
         send_event(fd, EV_KEY, KEY_B, 0);
         send_event(fd, EV_SYN, SYN_REPORT, 0);
      }
      if (returnKeyPress == 60) {
        // std::cout << "\t\t\tattempting to send to uinput . . .\n";
         
         send_event(fd, EV_KEY, KEY_ENTER, 1);
         send_event(fd, EV_SYN, SYN_REPORT, 0);
         delay(180);
         send_event(fd, EV_KEY, KEY_ENTER, 0);
         send_event(fd, EV_SYN, SYN_REPORT, 0);
      }
      
      delay(180);
   }
   
   if(ioctl(fd, UI_DEV_DESTROY) < 0)
      die("\t\t\t\terror: ioctl\n");
   
   close(fd);
   
   return 0 ;
}