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
   int button;
   int key;
} *io, // In main() this pointer is set to one of the two tables below.

io_0[] = {
   // This button/key table is used if the orientation is portrait
   // Input   Output (from /usr/include/linux/input.h)
   {   0,      KEY_A                 },
   {   1,      KEY_B                 },
   {   2,      KEY_C                 },
   {   3,      KEY_D                 },
   {   4,      KEY_E                 },
   {   5,      KEY_F                 },
   {   6,      KEY_G                 },
   {   7,      KEY_H                 },
   {   8,      KEY_I                 },
   {   9,      KEY_J                 },
   {   10,     KEY_K                 },
   {   11,     KEY_L                 },
   {   12,     KEY_M                 },
   {   13,     KEY_N                 },
   {   14,     KEY_O                 },
   {   15,     KEY_P                 },
   {   16,     KEY_Q                 },
   {   17,     KEY_R                 },
   {   18,     KEY_S                 },
   {   19,     KEY_T                 },
   {   20,     KEY_U                 },
   {   21,     KEY_V                 },
   {   22,     KEY_W                 },
   {   23,     KEY_X                 },
   {   24,     KEY_Y                 },
   {   25,     KEY_Z                 },
   {   26,     KEY_0                 },
   {   27,     KEY_1                 },
   {   28,     KEY_2                 },
   {   29,     KEY_3                 },
   {   30,     KEY_4                 },
   {   31,     KEY_5                 },
   {   32,     KEY_6                 },
   {   33,     KEY_7                 },
   {   34,     KEY_8                 },
   {   35,     KEY_9                 },
   {   36,     KEY_MINUS             },
   {   37,     KEY_DOT               },
   {   38,     KEY_BACKSLASH         },
   {   39,     KEY_SLASH             },
   {   40,     KEY_CAPSLOCK          },
   {   41,     KEY_LEFTSHIFT         },
   {   42,     KEY_LEFTCTRL          },
   {   43,     KEY_LEFTALT           },
   {   44,     KEY_SPACE             },
   {   45,     KEY_COMMA             },
   {   46,     KEY_KPASTERISK        },
   {   47,     KEY_KPPLUS            },
   {   48,     KEY_SEMICOLON         },
   {   49,     KEY_RIGHTCTRL         },
   {   50,     KEY_ESC               },
   {   51,     KEY_TAB               },
   {   52,     KEY_DELETE            },
   {   53,     KEY_APOSTROPHE        },
   {   54,     KEY_SPACE             },
   {   55,     KEY_SPACE             },
   {   56,     KEY_COMMA             },
   {   57,     KEY_DOT               },
   {   58,     KEY_BACKSPACE         },   
   {   59,     KEY_BACKSPACE         }, 
   {   -1,     -1                    } },   
   
io_90[] = {
   // This button/key table is used if the orientation is landscape
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
   {   59,     KEY_BACKSPACE         } };
   
   
      
unsigned char keyval;	//A variable
char
   *progName,                         // Program name (for error reporting)
   running      = 1;                 // Signal handler will set to 0 (exit
const int
   debounceTime = 20;                // 20 ms for button debouncing
   
      
      // Quick-n-dirty error reporter; print message, clean up and exit.
      void err(char *msg) {
         printf("%s: %s.  Try 'sudo %s'.\n", progName, msg, progName);
         //cleanup();
         exit(1);
      }
      
 
/*
 * + *---------------------------------------+
 * | Prototype: void pin_init(void);       |
 * | Return Type: void                     |
 * | Arguments: None                       |
 * | Description: Initialize pins and      |
 * |              Keypad.                  |
 * +---------------------------------------+
 */
void pin_init(){
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
      {0,   1,  2,  3,  4,  5},
      {6,   7,  8,  9, 10, 11},
      {12, 13, 14, 15, 16, 17},
      {18, 19, 20, 21, 22, 23}, 
      {24, 25, 26, 27, 28, 29},
      {30, 31, 32, 33, 34, 35},
      {36, 37, 38, 39, 40, 41},
      {42, 43, 44, 45, 46, 47},
      {48, 49, 50, 51, 52, 53},
      {54, 55, 56, 57, 58, 59}
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
               
               //std::cout << "\nROW: " << rowCount << "\tCOLUMN: " << columnCount << "\tKEY: " << key << "\n";
               
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
               
               if(keyPadBool[0][0] and keyPadBool[0][1] == 1)
               {
                  //std::cout << "\t\t\tKey combination 1 and 58 -- ROTATE 270 . . .\n";
                  std::cout << "\tKeypad_Driver_V03 -- check 02, 16:13; compile test.\n";
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
   delay(80);
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
	int                    key,
                          fd,           // For mmap, sysfs, uinput
	                       i, j,         // Asst. counter
	                       bitmask;      // Pullup enable bitmask
                          
	                       
	unsigned long          bitMask, bit; // For Vulcan pinch detect
	volatile unsigned char shortWait;    // Delay counter
	struct input_event     keyEv, synEv; // uinput events
	//struct pollfd          p[32];        // GPIO file descriptors

	progName = argv[0];             // For error reporting


   
   // Select io[] table for orientation.  0 or 90
   //    io = (access("/etc/modprobe.d/adafruit.conf", F_OK) ||
   //    access("/dev/fb1", F_OK)) ? ioStandard : ioTFT;
   io = io_0;
   
   
   pin_init();
   
   int returnKeyPress = 0;
   int returnKeyPress_01 = 0;
   int debounce = 100;


   // Normally uses /dev/uinput for generating key events.
	if((fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK)) < 0)
		err("Can't open /dev/uinput");
	if(ioctl(fd, UI_SET_EVBIT, EV_KEY) < 0)
		err("Can't SET_EVBIT");
	for(i=0; io[i].button >= 0; i++) {
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

	// Initialize input event structures
	memset(&keyEv, 0, sizeof(keyEv));
	keyEv.type  = EV_KEY;
	memset(&synEv, 0, sizeof(synEv));
	synEv.type  = EV_SYN;
	synEv.code  = SYN_REPORT;
	synEv.value = 0;

	// 'fd' is now open file descriptor for issuing uinput events

   while(1)
   {
      returnKeyPress = get_key();
      //if (returnKeyPress == 1) {
         // std::cout << "\t\t\tattempting to send to uinput . . .\n";

      switch ( returnKeyPress ) {
         case 0:
            send_event(fd, EV_KEY, KEY_A, 1);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            delay(debounce);
            send_event(fd, EV_KEY, KEY_A, 0);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            // std::cout << "\t\t\tattempting to send KEY_A . . .\n";
            break;
         case 1:
            send_event(fd, EV_KEY, KEY_B, 1);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            delay(debounce);
            send_event(fd, EV_KEY, KEY_B, 0);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
            break;
         case 2:
            send_event(fd, EV_KEY, KEY_C, 1);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            delay(debounce);
            send_event(fd, EV_KEY, KEY_C, 0);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            // std::cout << "\t\t\tattempting to send KEY_C . . .\n";
            break;
         case 3:
            send_event(fd, EV_KEY, KEY_D, 1);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            delay(debounce);
            send_event(fd, EV_KEY, KEY_D, 0);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            // std::cout << "\t\t\tattempting to send KEY_D . . .\n";
            break;
         case 4:
            send_event(fd, EV_KEY, KEY_E, 1);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            delay(debounce);
            send_event(fd, EV_KEY, KEY_E, 0);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            // std::cout << "\t\t\tattempting to send KEY_E . . .\n";
            break;
         case 5:
            send_event(fd, EV_KEY, KEY_F, 1);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            delay(debounce);
            send_event(fd, EV_KEY, KEY_F, 0);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            // std::cout << "\t\t\tattempting to send KEY_F . . .\n";
            break;
         case 6:
            send_event(fd, EV_KEY, KEY_G, 1);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            delay(debounce);
            send_event(fd, EV_KEY, KEY_G, 0);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            // std::cout << "\t\t\tattempting to send KEY_G . . .\n";
            break;
         case 7:
            send_event(fd, EV_KEY, KEY_H, 1);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            delay(debounce);
            send_event(fd, EV_KEY, KEY_H, 0);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            // std::cout << "\t\t\tattempting to send KEY_H . . .\n";
            break;
         case 8:
            send_event(fd, EV_KEY, KEY_I, 1);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            delay(debounce);
            send_event(fd, EV_KEY, KEY_I, 0);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            // std::cout << "\t\t\tattempting to send KEY_I . . .\n";
            break;
         case 9:
            send_event(fd, EV_KEY, KEY_J, 1);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            delay(debounce);
            send_event(fd, EV_KEY, KEY_J, 0);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            // std::cout << "\t\t\tattempting to send KEY_J . . .\n";
            break;
         case 10:
            send_event(fd, EV_KEY, KEY_K, 1);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            delay(debounce);
            send_event(fd, EV_KEY, KEY_K, 0);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            // std::cout << "\t\t\tattempting to send KEY_K . . .\n";
            break;
         case 11:
            send_event(fd, EV_KEY, KEY_L, 1);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            delay(debounce);
            send_event(fd, EV_KEY, KEY_L, 0);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            // std::cout << "\t\t\tattempting to send KEY_L . . .\n";
            break;
         case 12:
            send_event(fd, EV_KEY, KEY_M, 1);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            delay(debounce);
            send_event(fd, EV_KEY, KEY_M, 0);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            // std::cout << "\t\t\tattempting to send KEY_M . . .\n";
            break;
         case 13:
            send_event(fd, EV_KEY, KEY_N, 1);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            delay(debounce);
            send_event(fd, EV_KEY, KEY_N, 0);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            // std::cout << "\t\t\tattempting to send KEY_N . . .\n";
            break;
         case 14:
            send_event(fd, EV_KEY, KEY_O, 1);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            delay(debounce);
            send_event(fd, EV_KEY, KEY_O, 0);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            // std::cout << "\t\t\tattempting to send KEY_O . . .\n";
            break;
         case 15:
            send_event(fd, EV_KEY, KEY_P, 1);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            delay(debounce);
            send_event(fd, EV_KEY, KEY_P, 0);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            // std::cout << "\t\t\tattempting to send KEY_P . . .\n";
            break;
//          case 16:
//             send_event(fd, EV_KEY, KEY_Q, 1);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             delay(debounce);
//             send_event(fd, EV_KEY, KEY_Q, 0);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             // std::cout << "\t\t\tattempting to send KEY_Q . . .\n";
//             break;
         case 16:
            send_event(fd, EV_KEY, KEY_Q, 1);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            delay(debounce);
            send_event(fd, EV_KEY, KEY_Q, 0);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            // std::cout << "\t\t\tattempting to send KEY_Q . . .\n";
            break;
         case 17:
            send_event(fd, EV_KEY, KEY_R, 1);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            delay(debounce);
            send_event(fd, EV_KEY, KEY_R, 0);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            // std::cout << "\t\t\tattempting to send KEY_R . . .\n";
            break;
         case 18:
            send_event(fd, EV_KEY, KEY_S, 1);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            delay(debounce);
            send_event(fd, EV_KEY, KEY_S, 0);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            // std::cout << "\t\t\tattempting to send KEY_S . . .\n";
            break;
         case 19:
            send_event(fd, EV_KEY, KEY_T, 1);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            delay(debounce);
            send_event(fd, EV_KEY, KEY_T, 0);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            // std::cout << "\t\t\tattempting to send KEY_T . . .\n";
            break;
         case 20:
            send_event(fd, EV_KEY, KEY_U, 1);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            delay(debounce);
            send_event(fd, EV_KEY, KEY_U, 0);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            // std::cout << "\t\t\tattempting to send KEY_U . . .\n";
            break;
         case 21:
            send_event(fd, EV_KEY, KEY_V, 1);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            delay(debounce);
            send_event(fd, EV_KEY, KEY_V, 0);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            // std::cout << "\t\t\tattempting to send KEY_V . . .\n";
            break;
         case 22:
            send_event(fd, EV_KEY, KEY_W, 1);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            delay(debounce);
            send_event(fd, EV_KEY, KEY_W, 0);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            // std::cout << "\t\t\tattempting to send KEY_W . . .\n";
            break;
         case 23:
            send_event(fd, EV_KEY, KEY_X, 1);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            delay(debounce);
            send_event(fd, EV_KEY, KEY_X, 0);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            // std::cout << "\t\t\tattempting to send KEY_X . . .\n";
            break;
         case 24:
            send_event(fd, EV_KEY, KEY_Y, 1);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            delay(debounce);
            send_event(fd, EV_KEY, KEY_Y, 0);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            // std::cout << "\t\t\tattempting to send KEY_Y . . .\n";
            break;
         case 25:
            send_event(fd, EV_KEY, KEY_Z, 1);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            delay(debounce);
            send_event(fd, EV_KEY, KEY_Z, 0);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            // std::cout << "\t\t\tattempting to send KEY_Z . . .\n";
            break;
         case 26:
            send_event(fd, EV_KEY, KEY_Q, 1);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            delay(debounce);
            send_event(fd, EV_KEY, KEY_Q, 0);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
            break;
         case 27:
            send_event(fd, EV_KEY, KEY_B, 1);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            delay(debounce);
            send_event(fd, EV_KEY, KEY_B, 0);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
            break;
//          case 28:
//             send_event(fd, EV_KEY, KEY_B, 1);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             delay(debounce);
//             send_event(fd, EV_KEY, KEY_B, 0);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
//             break;
//          case 29:
//             send_event(fd, EV_KEY, KEY_B, 1);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             delay(debounce);
//             send_event(fd, EV_KEY, KEY_B, 0);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
//             break;
//          case 30:
//             send_event(fd, EV_KEY, KEY_B, 1);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             delay(debounce);
//             send_event(fd, EV_KEY, KEY_B, 0);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
//             break;
//          case 31:
//             send_event(fd, EV_KEY, KEY_B, 1);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             delay(debounce);
//             send_event(fd, EV_KEY, KEY_B, 0);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
//             break;
//          case 32:
//             send_event(fd, EV_KEY, KEY_B, 1);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             delay(debounce);
//             send_event(fd, EV_KEY, KEY_B, 0);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
//             break;
//          case 33:
//             send_event(fd, EV_KEY, KEY_B, 1);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             delay(debounce);
//             send_event(fd, EV_KEY, KEY_B, 0);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
//             break;
//          case 34:
//             send_event(fd, EV_KEY, KEY_B, 1);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             delay(debounce);
//             send_event(fd, EV_KEY, KEY_B, 0);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
//             break;
//          case 35:
//             send_event(fd, EV_KEY, KEY_B, 1);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             delay(debounce);
//             send_event(fd, EV_KEY, KEY_B, 0);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
//             break;
//          case 36:
//             send_event(fd, EV_KEY, KEY_B, 1);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             delay(debounce);
//             send_event(fd, EV_KEY, KEY_B, 0);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
//             break;
//          case 37:
//             send_event(fd, EV_KEY, KEY_B, 1);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             delay(debounce);
//             send_event(fd, EV_KEY, KEY_B, 0);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
//             break;
//          case 38:
//             send_event(fd, EV_KEY, KEY_B, 1);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             delay(debounce);
//             send_event(fd, EV_KEY, KEY_B, 0);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
//             break;
//          case 39:
//             send_event(fd, EV_KEY, KEY_B, 1);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             delay(debounce);
//             send_event(fd, EV_KEY, KEY_B, 0);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
//             break;
//          case 40:
//             send_event(fd, EV_KEY, KEY_B, 1);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             delay(debounce);
//             send_event(fd, EV_KEY, KEY_B, 0);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
//             break;
//          case 41:
//             send_event(fd, EV_KEY, KEY_B, 1);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             delay(debounce);
//             send_event(fd, EV_KEY, KEY_B, 0);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
//             break;
//          case 42:
//             send_event(fd, EV_KEY, KEY_B, 1);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             delay(debounce);
//             send_event(fd, EV_KEY, KEY_B, 0);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
//             break;
//          case 43:
//             send_event(fd, EV_KEY, KEY_B, 1);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             delay(debounce);
//             send_event(fd, EV_KEY, KEY_B, 0);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
//             break;
//          case 44:
//             send_event(fd, EV_KEY, KEY_B, 1);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             delay(debounce);
//             send_event(fd, EV_KEY, KEY_B, 0);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
//             break;
//          case 45:
//             send_event(fd, EV_KEY, KEY_B, 1);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             delay(debounce);
//             send_event(fd, EV_KEY, KEY_B, 0);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
//             break;
//          case 46:
//             send_event(fd, EV_KEY, KEY_B, 1);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             delay(debounce);
//             send_event(fd, EV_KEY, KEY_B, 0);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
//             break;
//          case 47:
//             send_event(fd, EV_KEY, KEY_B, 1);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             delay(debounce);
//             send_event(fd, EV_KEY, KEY_B, 0);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
//             break;
//          case 48:
//             send_event(fd, EV_KEY, KEY_B, 1);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             delay(debounce);
//             send_event(fd, EV_KEY, KEY_B, 0);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
//             break;
//          case 49:
//             send_event(fd, EV_KEY, KEY_B, 1);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             delay(debounce);
//             send_event(fd, EV_KEY, KEY_B, 0);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
//             break;
//          case 50:
//             send_event(fd, EV_KEY, KEY_B, 1);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             delay(debounce);
//             send_event(fd, EV_KEY, KEY_B, 0);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
//             break;
//          case 51:
//             send_event(fd, EV_KEY, KEY_B, 1);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             delay(debounce);
//             send_event(fd, EV_KEY, KEY_B, 0);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
//             break;
//          case 52:
//             send_event(fd, EV_KEY, KEY_B, 1);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             delay(debounce);
//             send_event(fd, EV_KEY, KEY_B, 0);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
//             break;
//          case 53:
//             send_event(fd, EV_KEY, KEY_B, 1);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             delay(debounce);
//             send_event(fd, EV_KEY, KEY_B, 0);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
//             break;
         case 54:
            send_event(fd, EV_KEY, KEY_BACKSPACE, 1);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            delay(debounce);
            send_event(fd, EV_KEY, KEY_BACKSPACE, 0);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
            break;
//          case 55:
//             send_event(fd, EV_KEY, KEY_B, 1);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             delay(debounce);
//             send_event(fd, EV_KEY, KEY_B, 0);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
//             break;
//          case 56:
//             send_event(fd, EV_KEY, KEY_B, 1);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             delay(debounce);
//             send_event(fd, EV_KEY, KEY_B, 0);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
//             break;
//          case 57:
//             send_event(fd, EV_KEY, KEY_B, 1);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             delay(debounce);
//             send_event(fd, EV_KEY, KEY_B, 0);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
//             break;
         case 58:
            send_event(fd, EV_KEY, KEY_ENTER, 1);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            delay(debounce);
            send_event(fd, EV_KEY, KEY_ENTER, 0);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
            break;
         case 59:
            send_event(fd, EV_KEY, KEY_ENTER, 1);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            delay(debounce);
            send_event(fd, EV_KEY, KEY_ENTER, 0);
            send_event(fd, EV_SYN, SYN_REPORT, 0);
            // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
            break;
//          case 60:
//             send_event(fd, EV_KEY, KEY_B, 1);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             delay(debounce);
//             send_event(fd, EV_KEY, KEY_B, 0);
//             send_event(fd, EV_SYN, SYN_REPORT, 0);
//             // std::cout << "\t\t\tattempting to send KEY_B . . .\n";
//             break;
         default:
            break;
      }
   }
      return 0;
}