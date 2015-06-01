/*
 * Example of keystrokes sent from userland. Rafael Zurita 2014
 * Useful to work with on screen keyboard 
 * The fb on screen keyboard would send keystrokes using uinput driver
 * There is already a kernel driver, so we use it in this example
 * (the kernel driver is uinput)
 *
 * This example sends KEY_D events to the system from a user program. 
 * During 20 seconds
 *
 * Based on http://thiemonge.org/getting-started-with-uinput
 *
 * Usage: 
 *   gcc -o userland_keystrokes. userland_keystrokes.c 
 *   modprobe uinput
 *   ./userland_keystrokes
 */

#define UINPUT_MAX_NAME_SIZE    80
#include <fcntl.h>
#include <linux/ioctl.h>
#include <unistd.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define TRUE 1
#define FALSE 0

#define PRESS 1
#define RELEASE 0

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
   
   void key_init(void){
      //std::cout << "\tSetup GPIO . . .\n";
   }
   
//      Prototype: unsigned int get_key(void);      
//      Return Type: unsigned int                   
//      Arguments: None                             
//      Description: To read key from the keypad    
    
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
      
      //int column[6] = {col0, col1, col2, col3, col4, col5};
      
      //int row[10] = {row0, row1, row2, row3, row4, row5, row6, row7, row8, row9};
      
      int columnTest = 0;
      int columnCount = 0;
      int rowTest = 0;
      int rowCount = 0;
      
      int key = 0;
      int keyPress = 0;
      int keyToggle = 0;
      int numberOfPresses = 0;
      
//       while (keyPress == 0) //and (rowTest == 0)) // While no key pressed
//       {
//          // Testcase
//          int fd, bytes;
//          struct input_event data;
//          
//          const char *pDevice = "/dev/input/event4";
//          
//          // Open Keyboard
//          fd = open(pDevice, O_RDONLY | O_NONBLOCK);
//          if(fd == -1)
//          {
//             printf("ERROR Opening %s\n", pDevice);
//             return -1;
//          }
//          
//             // Read Keyboard Data
//             bytes = read(fd, &data, sizeof(data));
//             if(bytes > 0)
//             {
// //                printf("Keypress value=%x, type=%x, code=%x\n", data.value, data.type, data.code);
//                keyPress = data.value;
//                rowTest = 1;
//             }
//             else
//             {
//                // Nothing read
//                //sleep(1);
//             }
//          }
      return (key);  // Return key number
   }    
   
void main(void){
	int fd;
	/* Set up a fake keyboard device */
	fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK); // or /dev/input/uinput
	ioctl(fd, UI_SET_EVBIT, EV_KEY);

	/* Send an event */
	int ret;
	ret = ioctl(fd, UI_SET_EVBIT, EV_KEY);
	ret = ioctl(fd, UI_SET_EVBIT, EV_SYN);
	ret = ioctl(fd, UI_SET_KEYBIT, KEY_D);

	struct uinput_user_dev {
	    char name[UINPUT_MAX_NAME_SIZE];
	    struct input_id id;
       	 int ff_effects_max;
       	 int absmax[ABS_MAX + 1];
       	 int absmin[ABS_MAX + 1];
       	 int absfuzz[ABS_MAX + 1];
       	 int absflat[ABS_MAX + 1];
	};

	struct uinput_user_dev uidev;
	memset(&uidev, 0, sizeof(uidev));

	snprintf(uidev.name, UINPUT_MAX_NAME_SIZE, "uinput-sample");
	uidev.id.bustype = BUS_USB;
	uidev.id.vendor  = 0x1234;
	uidev.id.product = 0xfedc;
	uidev.id.version = 1;

	ret = write(fd, &uidev, sizeof(uidev));
	ret = ioctl(fd, UI_DEV_CREATE);


	struct input_event ev;

	memset(&ev, 0, sizeof(ev));

	int i;
	for (i=0;i<20;i++) {
		ev.type = EV_KEY;
		ev.code = KEY_D;
		ev.value = 1;

		ret = write(fd, &ev, sizeof(ev));
		sleep(1);

		ev.value = 0;
		ret = write(fd, &ev, sizeof(ev));
	}

	/* Clean up */
	ioctl(fd, UI_DEV_DESTROY);
	close(fd);
}
