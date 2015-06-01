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

#include <string.h>
#include <poll.h>
#include <signal.h>
#include <sys/mman.h>

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

#define GND -1

struct {
   int pin;
   int key;
} *io, // In main() this pointer is set to one of the two tables below.

io_0[] = {
   // This pin/key table is used if the orientation is portrait
   // Input   Output (from /usr/include/linux/input.h)
   {   1,      KEY_A                 },
   {   2,      KEY_B                 },
   {   3,      KEY_C                 },
   {   4,      KEY_D                 },
   {   5,      KEY_E                 },
   {   6,      KEY_F                 },
   {   7,      KEY_G                 },
   {   8,      KEY_H                 },
   {   9,      KEY_I                 },
   {   10,     KEY_J                 },
   {   11,     KEY_K                 },
   {   12,     KEY_L                 },
   {   13,     KEY_M                 },
   {   14,     KEY_N                 },
   {   15,     KEY_O                 },
   {   16,     KEY_P                 },
   {   17,     KEY_Q                 },
   {   18,     KEY_R                 },
   {   19,     KEY_S                 },
   {   20,     KEY_T                 },
   {   21,     KEY_U                 },
   {   22,     KEY_V                 },
   {   23,     KEY_W                 },
   {   24,     KEY_X                 },
   {   25,     KEY_Y                 },
   {   26,     KEY_Z                 },
   {   27,     KEY_0                 },
   {   28,     KEY_1                 },
   {   29,     KEY_2                 },
   {   30,     KEY_3                 },
   {   31,     KEY_4                 },
   {   32,     KEY_5                 },
   {   33,     KEY_6                 },
   {   34,     KEY_7                 },
   {   35,     KEY_8                 },
   {   36,     KEY_9                 },
   {   37,     KEY_MINUS             },
   {   38,     KEY_DOT               },
   {   39,     KEY_BACKSLASH         },
   {   40,     KEY_SLASH             },
   {   41,     KEY_CAPSLOCK          },
   {   42,     KEY_LEFTSHIFT         },
   {   43,     KEY_LEFTCTRL          },
   {   44,     KEY_LEFTALT           },
   {   45,     KEY_SPACE             },
   {   46,     KEY_COMMA             },
   {   47,     KEY_KPASTERISK        },
   {   48,     KEY_KPPLUS            },
   {   49,     KEY_SEMICOLON         },
   {   50,     KEY_RIGHTCTRL         },
   {   51,     KEY_ESC               },
   {   52,     KEY_TAB               },
   {   53,     KEY_DELETE            },
   {   54,     KEY_APOSTROPHE        },
   {   55,     KEY_SPACE             },
   {   56,     KEY_SPACE             },
   {   57,     KEY_COMMA             },
   {   58,     KEY_DOT               },
   {   59,     KEY_BACKSPACE         },
   {   60,     KEY_ENTER             },
   {   61,     KEY_DOWN              },
   {   62,     KEY_LEFT              },
   {   63,     KEY_RIGHT             },
   {  -1,     -1           } },
   
io_90[] = {
   // This pin/key table is used if the orientation is landscape
   // Input   Output (from /usr/include/linux/input.h)
   {   1,      KEY_A                 },
   {   2,      KEY_B                 },
   {   3,      KEY_C                 },
   {   4,      KEY_D                 },
   {   5,      KEY_E                 },
   {   6,      KEY_F                 },
   {   7,      KEY_G                 },
   {   8,      KEY_H                 },
   {   9,      KEY_I                 },
   {   10,     KEY_J                 },
   {   11,     KEY_K                 },
   {   12,     KEY_L                 },
   {   13,     KEY_M                 },
   {   14,     KEY_N                 },
   {   15,     KEY_O                 },
   {   16,     KEY_P                 },
   {   17,     KEY_Q                 },
   {   18,     KEY_R                 },
   {   19,     KEY_S                 },
   {   20,     KEY_T                 },
   {   21,     KEY_U                 },
   {   22,     KEY_V                 },
   {   23,     KEY_W                 },
   {   24,     KEY_X                 },
   {   25,     KEY_Y                 },
   {   26,     KEY_Z                 },
   {   27,     KEY_0                 },
   {   28,     KEY_1                 },
   {   29,     KEY_2                 },
   {   30,     KEY_3                 },
   {   31,     KEY_4                 },
   {   32,     KEY_5                 },
   {   33,     KEY_6                 },
   {   34,     KEY_7                 },
   {   35,     KEY_8                 },
   {   36,     KEY_9                 },
   {   37,     KEY_MINUS             },
   {   38,     KEY_DOT               },
   {   39,     KEY_BACKSLASH         },
   {   40,     KEY_SLASH             },
   {   41,     KEY_CAPSLOCK          },
   {   42,     KEY_LEFTSHIFT         },
   {   43,     KEY_LEFTCTRL          },
   {   44,     KEY_LEFTALT           },
   {   45,     KEY_SPACE             },
   {   46,     KEY_COMMA             },
   {   47,     KEY_KPASTERISK        },
   {   48,     KEY_KPPLUS            },
   {   49,     KEY_SEMICOLON         },
   {   50,     KEY_RIGHTCTRL         },
   {   51,     KEY_ESC               },
   {   52,     KEY_TAB               },
   {   53,     KEY_DELETE            },
   {   54,     KEY_APOSTROPHE        },
   {   55,     KEY_SPACE             },
   {   56,     KEY_SPACE             },
   {   57,     KEY_COMMA             },
   {   58,     KEY_DOT               },
   {   59,     KEY_BACKSPACE         },
   {   60,     KEY_ENTER             },
   {   61,     KEY_DOWN              },
   {   62,     KEY_LEFT              },
   {   63,     KEY_RIGHT             },
   {  -1,     -1           } };
      
unsigned char keyval;	//A variable
char
   *progName,                         // Program name (for error reporting)
   //sysfs_root[] = "/sys/class/gpio", // Location of Sysfs GPIO files
   running      = 1;                 // Signal handler will set to 0 (exit
const int
   debounceTime = 20;                // 20 ms for button debouncing
   
      
      // Quick-n-dirty error reporter; print message, clean up and exit.
      void err(char *msg) {
         printf("%s: %s.  Try 'sudo %s'.\n", progName, msg, progName);
         //cleanup();
         exit(1);
      }
      
      // Un-export any Sysfs pins used; don't leave filesystem cruft.  Also
      // restores any GND pins to inputs.  Write errors are ignored as pins
      // may be in a partially-initialized state.
//       void cleanup() {
//          char buf[50];
//          int  fd, i;
//          sprintf(buf, "%s/unexport", sysfs_root);
//          if((fd = open(buf, O_WRONLY)) >= 0) {
//             for(i=0; io[i].pin >= 0; i++) {
//                // Restore GND items to inputs
//                if(io[i].key == GND)
//                   pinConfig(io[i].pin, "direction", "in");
//                // And un-export all items regardless
//                sprintf(buf, "%d", io[i].pin);
//                write(fd, buf, strlen(buf));
//             }
//             close(fd);
//          }
//       }
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
                  std::cout << "\t\t\tKey combination 1 and 58 -- ROTATE 180 . . .\n";
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
                  std::cout << "\t\t\tKey combination 1 and 58 -- ROTATE 270 . . .\n";
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
	char                   buf[50],      // For sundry filenames
	                       c,            // Pin input value ('0'/'1')
	                       board;        // 0=Pi1Rev1, 1=Pi1Rev2, 2=Pi2
	int                    fd,           // For mmap, sysfs, uinput
	                       i, j,         // Asst. counter
	                       bitmask,      // Pullup enable bitmask
	                       timeout = -1, // poll() timeout
	                       intstate[60], // Last-read state
	                       extstate[60], // Debounced state
	                       lastKey = -1; // Last key down (for repeat)
	unsigned long          bitMask, bit; // For Vulcan pinch detect
	volatile unsigned char shortWait;    // Delay counter
	struct input_event     keyEv, synEv; // uinput events
	//struct pollfd          p[32];        // GPIO file descriptors

	progName = argv[0];             // For error reporting
	//signal(SIGINT , signalHandler); // Trap basic signals (exit cleanly)
	//signal(SIGKILL, signalHandler);

   int                    key;
   
   // Select io[] table for Cupcade (TFT) or 'normal' project.
   //    io = (access("/etc/modprobe.d/adafruit.conf", F_OK) ||
   //    access("/dev/fb1", F_OK)) ? ioStandard : ioTFT;
   io = io_0;
   
   key_init();
   
   // Set up uinput
   //    struct uinput_user_dev device;
   //    memset(&device, 0, sizeof device);
   
  /* if((fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK)) < 0)
      err("Can't open /dev/uinput");
   if(ioctl(fd, UI_SET_EVBIT, EV_KEY) < 0)
      err("Can't SET_EVBIT");
   for(i=0; io[i].pin >= 0; i++) {
      if(io[i].key != GND) {
         if(ioctl(fd, UI_SET_KEYBIT, io[i].key) < 0)
            err("Can't SET_KEYBIT");
      }
   }
   
   struct uinput_user_dev uidev;
   memset(&uidev, 0, sizeof(uidev));
   snprintf(uidev.name, UINPUT_MAX_NAME_SIZE, "Keypad_Driver");
   uidev.id.bustype = BUS_USB;
   uidev.id.vendor  = 0x1;
   uidev.id.product = 0x1;
   uidev.id.version = 1;
   if(write(fd, &uidev, sizeof(uidev)) < 0)
      err("write failed");
   if(ioctl(fd, UI_DEV_CREATE) < 0)
      err("DEV_CREATE failed");
   
   struct input_event ev;
   
   memset(&ev, 0, sizeof(ev));
            
   // Initialize input event structures
   memset(&keyEv, 0, sizeof(keyEv));
   keyEv.type  = EV_KEY;
   memset(&synEv, 0, sizeof(synEv));
   synEv.type  = EV_SYN;
   synEv.code  = SYN_REPORT;
   synEv.value = 0;
   
   // 'fd' is now open file descriptor for issuing uinput events
   
   
   // ----------------------------------------------------------------
   // Monitor GPIO file descriptors for button events.  The poll()
   // function watches for GPIO IRQs in this case; it is NOT
   // continually polling the pins!  Processor load is near zero.
   
   
   //std::cout << "\tSetup uinput complete . . .\n";
   
   
   */
  
//    int returnKeyPress = 0;
//    
//    while(running)
//    {
//       returnKeyPress = get_key();
//      // std::cout << "\t\tButton press = " << returnKeyPress << "\n";
// 
//       keyEv.code  = io[returnKeyPress].key;
      
//       {
//          ev.type = EV_KEY;
//          ev.code = KEY_D;
//          ev.value = 1;
//          
//          ret = write(fd, &ev, sizeof(ev));
//          sleep(1);
//          
//          ev.value = 0;
//          ret = write(fd, &ev, sizeof(ev));
//       }
      
//       if (returnKeyPress == 1) {
//         // std::cout << "\t\t\tattempting to send to uinput . . .\n";
// 
//          keyEv.code  = io[returnKeyPress].key;
//          keyEv.value = intstate[returnKeyPress];
//          
//          send_event(fd, EV_KEY, KEY_A, 1);
//          send_event(fd, EV_SYN, SYN_REPORT, 0);
//          delay(180);
//          send_event(fd, EV_KEY, KEY_A, 0);
//          send_event(fd, EV_SYN, SYN_REPORT, 0);
//       }
//       if (returnKeyPress == 2) {
//          std::cout << "\t\t\tattempting to send to uinput . . . Button press = " << returnKeyPress << "\n";
//          if (ioctl(fd,UI_SET_EVBIT,EV_KEY) < 0)
//             fprintf(stderr, "\t\terror evbit key\n");
//          
//          if (ioctl(fd,UI_SET_KEYBIT, KEY_B) < 0)
//             fprintf(stderr, "\t\terror evbit key\n");
//          
//          if (ioctl(fd,UI_SET_EVBIT,EV_REL) < 0)
//             fprintf(stderr, "\t\terror evbit rel\n");
//          
//          send_event(fd, EV_KEY, KEY_B, 1);
//          send_event(fd, EV_SYN, SYN_REPORT, 0);
//          delay(180);
//          send_event(fd, EV_KEY, KEY_B, 0);
//          send_event(fd, EV_SYN, SYN_REPORT, 0);
//       }
//       if (returnKeyPress == 60) {
//         // std::cout << "\t\t\tattempting to send to uinput . . .\n";
//          
//          send_event(fd, EV_KEY, KEY_ENTER, 1);
//          send_event(fd, EV_SYN, SYN_REPORT, 0);
//          delay(180);
//          send_event(fd, EV_KEY, KEY_ENTER, 0);
//          send_event(fd, EV_SYN, SYN_REPORT, 0);
//       }
//       
//       delay(180);
//    }
//    
//    if(ioctl(fd, UI_DEV_DESTROY) < 0)
//       die("\t\t\t\terror: ioctl\n");
//    
//    close(fd);
//    
//    return 0 ;


// A few arrays here are declared with 32 elements, even though
	// values aren't needed for io[] members where the 'key' value is
	// GND.  This simplifies the code a bit -- no need for mallocs and
	// tests to create these arrays -- but may waste a handful of
	// bytes for any declared GNDs.
// 	char                   buf[50],      // For sundry filenames
// 	                       c,            // Pin input value ('0'/'1')
// 	                       board;        // 0=Pi1Rev1, 1=Pi1Rev2, 2=Pi2
// 	int                    fd,           // For mmap, sysfs, uinput
// 	                       i, j,         // Asst. counter
// 	                       bitmask,      // Pullup enable bitmask
// 	                       timeout = -1, // poll() timeout
// 	                       intstate[32], // Last-read state
// 	                       extstate[32], // Debounced state
// 	                       lastKey = -1; // Last key down (for repeat)
// 	unsigned long          bitMask, bit; // For Vulcan pinch detect
// 	volatile unsigned char shortWait;    // Delay counter
// 	struct input_event     keyEv, synEv; // uinput events
// 	struct pollfd          p[32];        // GPIO file descriptors
// 
// 	progName = argv[0];             // For error reporting
// 	signal(SIGINT , signalHandler); // Trap basic signals (exit cleanly)
// 	signal(SIGKILL, signalHandler);

	// Select io[] table for Cupcade (TFT) or 'normal' project.
// 	io = (access("/etc/modprobe.d/adafruit.conf", F_OK) ||
// 	      access("/dev/fb1", F_OK)) ? ioStandard : ioTFT;
   io = io_0;

//struct input_event     keyEv, synEv; // uinput events

int returnKeyPress = 0;



// Retrogame normally uses /dev/uinput for generating key events.
	// Cupcade requires this and it's the default.  SDL2 (used by
	// some newer emulators) doesn't like it, wants /dev/input/event0
	// instead.  Enable that code by changing to "#if 0" above.
	if((fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK)) < 0)
		err("Can't open /dev/uinput");
	if(ioctl(fd, UI_SET_EVBIT, EV_KEY) < 0)
		err("Can't SET_EVBIT");
	for(i=0; io[i].pin >= 0; i++) {
		if(io[i].key != GND) {
			if(ioctl(fd, UI_SET_KEYBIT, io[i].key) < 0)
				err("Can't SET_KEYBIT");
		}
	}
	//if(ioctl(fd, UI_SET_KEYBIT, vulcanKey) < 0) err("Can't SET_KEYBIT");
	struct uinput_user_dev uidev;
	memset(&uidev, 0, sizeof(uidev));
	snprintf(uidev.name, UINPUT_MAX_NAME_SIZE, "retrogame");
	uidev.id.bustype = BUS_USB;
	uidev.id.vendor  = 0x1;
	uidev.id.product = 0x1;
	uidev.id.version = 1;
	if(write(fd, &uidev, sizeof(uidev)) < 0)
		err("write failed");
	if(ioctl(fd, UI_DEV_CREATE) < 0)
		err("DEV_CREATE failed");

	// Initialize input event structures
	memset(&keyEv, 0, sizeof(keyEv));
	keyEv.type  = EV_KEY;
	memset(&synEv, 0, sizeof(synEv));
	synEv.type  = EV_SYN;
	synEv.code  = SYN_REPORT;
	synEv.value = 0;

	// 'fd' is now open file descriptor for issuing uinput events

   while(running)
   {
      returnKeyPress = get_key();
      // std::cout << "\t\tButton press = " << returnKeyPress << "\n";
      
      keyEv.code  = io[returnKeyPress].key;
      //keyEv.code  = io[i].key;
      keyEv.value = 1;
      write(fd, &keyEv,
         sizeof(keyEv));
      delay(180);
      keyEv.value = 0;
      write(fd, &keyEv,
         sizeof(keyEv));
   }
   
   /*
for(c=i=j=0; io[i].pin >= 0; i++, bit<<=1) {
   if(io[i].key != GND) {
      // Compare internal state against
      // previously-issued value.  Send
      // keystrokes only for changed states.
      if(intstate[j] != extstate[j]) {
         extstate[j] = intstate[j];
         keyEv.code  = io[i].key;
         keyEv.value = intstate[j];
         write(fd, &keyEv,
               sizeof(keyEv));
         c = 1; // Follow w/SYN event
         if(intstate[j]) { // Press?
            // Note pressed key
            // and set initial
            // repeat interval.
            lastKey = i;
            timeout = repTime1;
         } else { // Release?
            // Stop repeat and
            // return to normal
            // IRQ monitoring
            // (no timeout).
            lastKey = timeout = -1;
         }
      }
      j++;
      if(intstate[i]) bitMask |= bit;
   }
}*/
   
}