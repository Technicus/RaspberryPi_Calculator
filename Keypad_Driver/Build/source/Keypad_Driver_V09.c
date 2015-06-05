
/*
 * This is a keypad driver for a 60 button matrix connected to a Raspberry Pi.
 * 
 */



#include <fcntl.h>
#include <linux/fb.h>
#include <linux/input.h>
#include <linux/ioctl.h>
#include <linux/uinput.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/time.h>
#include <termios.h>
#include <unistd.h>

// from version 6
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
#include <stdbool.h>
#include <iostream>

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

#define dpadLSB 14
#define dpadMSB 15
#define dpadRead 18

// #define up 18
// #define down 15
// #define left 14

#define TRUE 1
#define FALSE 0

#define GND -1
// end from version 6


/* key codes REFERENCE : from /usr/include/linux/input.h
#define KEY_Q			16
#define KEY_W			17
#define KEY_E			18
#define KEY_R			19
#define KEY_T			20
#define KEY_Y			21
#define KEY_U			22
#define KEY_I			23
#define KEY_O			24
#define KEY_P			25
#define KEY_LEFTBRACE		26
#define KEY_RIGHTBRACE		27
#define KEY_ENTER		28
#define KEY_LEFTCTRL		29
#define KEY_A			30
#define KEY_S			31
#define KEY_D			32
#define KEY_F			33
#define KEY_G			34
#define KEY_H			35
#define KEY_J			36
#define KEY_K			37
#define KEY_L			38
#define KEY_SEMICOLON		39
#define KEY_APOSTROPHE		40
#define KEY_GRAVE		41
#define KEY_LEFTSHIFT		42
#define KEY_BACKSLASH		43
#define KEY_Z			44
#define KEY_X			45
#define KEY_C			46
#define KEY_V			47
#define KEY_B			48
#define KEY_N			49
#define KEY_M			50

#define KEY_ESC			1
#define KEY_1			2
#define KEY_2			3
#define KEY_3			4
#define KEY_4			5
#define KEY_5			6
#define KEY_6			7
#define KEY_7			8
#define KEY_8			9
#define KEY_9			10
#define KEY_0			11
#define KEY_MINUS		12
#define KEY_EQUAL		13
#define KEY_BACKSPACE		14
#define KEY_TAB			15

#define KEY_RIGHTCTRL		97
#define KEY_KPSLASH		98
#define KEY_SYSRQ		99
#define KEY_RIGHTALT		100
#define KEY_LINEFEED		101
#define KEY_HOME		102
#define KEY_PAGEUP		104
#define KEY_END			107
#define KEY_PAGEDOWN		109
#define KEY_INSERT		110
#define KEY_DELETE		111
#define KEY_SPACE		57

#define KEY_UP			103
#define KEY_DOWN		108
#define KEY_LEFT		105
#define KEY_RIGHT		106

*/


unsigned char abc[] = { 30, 48, 46, 32, 18, 33,       // A, B, C, D, E, F
                        34, 35, 23, 36, 37, 38,       // G, H, I, J, K, L
                        50, 49, 24, 25, 16, 16,       // M, N, O, P,  , Q
                        19, 31, 20, 22, 47, 17,       // R, S, T, Y, V, W, 
                        45, 21, 44, 14, 28, 57,      // X, Y, Z, BACKSPACE, ENTER, SPACE
                        103, 108, 105, 106 };         // UP, DOWN, LEFT, RIGHT
                       
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
                                                                                                
//    pullUpDnControl (up, PUD_DOWN);    // Directional Switch Up                                
//    pullUpDnControl (down, PUD_DOWN);  // Directional Switch Down                               
//    pullUpDnControl (left, PUD_DOWN);  // Directional Switch Left
   
   // setup dpad pins multiuplexer4
   pinMode (dpadLSB, OUTPUT);         // dpadLSB         
   pinMode (dpadMSB, OUTPUT);         // dpadLSB    
   digitalWrite (dpadLSB, LOW);
   digitalWrite (dpadMSB, LOW);
   pinMode (dpadRead, INPUT);         // set dpadRead pin as input
   pullUpDnControl (dpadRead, PUD_UP); // set read internal pullup
}

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
   
//   int columnTest = 0;
   int columnCount = 0;
   int rowTest = 0;
   int rowCount = 0;
   
   int key = 0;
   int keyPress = 0;
//    int keyToggle = 0;
//    int numberOfPresses = 0;
//    
//    int pinToggle_0 = 0;
//    int pinToggle_1 = 0;
//    int pinCheck = 1;
//    
   while ((keyPress == 0 and rowTest == 0)) // While no key pressed
   {
      for ( columnCount = 0; columnCount <= 5; columnCount++  )
      {
         
         digitalWrite(dpadMSB, (columnCount & 0x02) >> 1);
         digitalWrite(dpadLSB, (columnCount & 0x01));
         
         delayMicroseconds(1);
         
         bool bitChecker = !digitalRead(dpadRead);
         
         switch (columnCount)
         {
            case 0:
               if (bitChecker)
               {
                  //printf("\tDPAD: LEFT;\n");    
                  delay(200);
                  key = 32;
                  return (key);
               }
               break;
            case 1:
               if (bitChecker)
               {
                  //printf("\tDPAD: RIGHT;\n");
                  delay(200);
                  key = 33;
                  return (key);
               }
               break;              
            case 2:
               if (bitChecker)
               {
                  //printf("\tDPAD: DOWN;\n");    
                  delay(200);
                  key = 31;
                  return (key);
               }
               break;
            case 3:
               if (bitChecker)
               {
                  //printf("\tDPAD:  UP;\n");    
                  delay(200);
                  key = 30;
                  return (key);
               }
               break;                 
         }
         
         
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
                  std::cout << "\t\t\tKey combination 0 and 5 -- UPDATE . . .\n";
                  delay(180);
                  //system("runuser -l pi -c '/home/pi/Calculator/Software/Build/compile/update.sh'");
                  system("/home/pi/Calculator/Software/Build/compile/update.sh");
               }
               if(keyPadBool[0][0] and keyPadBool[0][6] == 1)
               {
                  std::cout << "\t\t\tKey combination 0 and 6 -- Start Calculator . . .\n";
                  delay(180);
                  system("sudo /usr/local/bin/SimpleCalculator &");
               } 
               if(keyPadBool[0][0] and keyPadBool[0][7] == 1)
               {
                  std::cout << "\t\t\tKey combination 0 and 6 -- Stop Calculator . . .\n";
                  delay(180);
                  system("sudo kill `pgrep SimpleCalculato` &");
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
                  std::cout << "\tKeypad_Driver_V07 -- check 00, 12:19; Check DPAD.\n";
               }
               if(keyPadBool[0][0] and keyPadBool[0][2] == 1)
               {
                  //std::cout << "\t\t\tKey combination 1 and 58 -- ROTATE 270 . . .\n";
                  std::cout << "\tKeypad orientation = ?"; //, reportOrientation();
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
   delay(200);
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
        fprintf(stderr, "Error on send_event");
        return -1;
    }

    return 0;
}

int main(void) {

//      int fbfd = 0;
//      char *fbp = 0;
//      int x = 0, y = 0;
//      long int location = 0;

	/* uinput init */
	int i,fd;
	struct uinput_user_dev device;
	memset(&device, 0, sizeof device);

	fd=open("/dev/uinput",O_WRONLY);
	strcpy(device.name,"test keyboard");

	device.id.bustype=BUS_USB;
	device.id.vendor=1;
	device.id.product=1;
	device.id.version=1;

	if (write(fd,&device,sizeof(device)) != sizeof(device))
	{
		fprintf(stderr, "error setup\n");
	}

	if (ioctl(fd,UI_SET_EVBIT,EV_KEY) < 0)
		fprintf(stderr, "error evbit key\n");
   
   //for (i=0;i<27;i++)
   for (i=0;i<63;i++)
      if (ioctl(fd,UI_SET_KEYBIT, abc[i]) < 0)
			fprintf(stderr, "error evbit key\n");

	if (ioctl(fd,UI_SET_EVBIT,EV_REL) < 0)
		fprintf(stderr, "error evbit rel\n");

	for(i=REL_X;i<REL_MAX;i++)
		if (ioctl(fd,UI_SET_RELBIT,i) < 0)
			fprintf(stderr, "error setrelbit %d\n", i);

	if (ioctl(fd,UI_DEV_CREATE) < 0)
	{
		fprintf(stderr, "error create\n");
	}

	sleep(2);
	/* end uinput init */

	/* init event0 */
	int fdkey;
	fdkey = open("/dev/input/event0", O_RDONLY);
	// struct input_event evkey;

	int flags = fcntl(fd, F_GETFL, 0);
	//int err;
	fcntl(fdkey, F_SETFL, flags | O_NONBLOCK);
	/* end init event0 */

   pin_init();
   
	//int j, m=0,k;
   int returnKeyPress = 0;
   
	while(1) {
		/* check for key */
// 		k=0;
// 		err=-1;
// 		while ((err==-1) && (k<500)) {
// 			err = read(fdkey, &evkey, sizeof(struct input_event));
// 			k++;
// 			usleep(1000);
// 		}
// 
// 		if (err!=-1) {
// 			if ((evkey.type==1) && (evkey.value==0)) {
// 
// 				if ((m==27) || (m==28)) break;
// 				send_event(fd, EV_KEY, abc[m], 1);
// 				send_event(fd, EV_SYN, SYN_REPORT, 0);
// 				send_event(fd, EV_KEY, abc[m], 0);
// 				send_event(fd, EV_SYN, SYN_REPORT, 0);
// 			} else {
// 				if (m==0)
// 					m=27;
// 				else
// 					m--;
// 			}
// 			//printf("%i",m);
// 		}
      
		returnKeyPress = get_key();
      //printf("returnKeyPress = %d, abc[%d] = %d \n", returnKeyPress, returnKeyPress, abc[returnKeyPress]);
      //evkey.type==1;
      //evkey.value==0;
      send_event(fd, EV_KEY, abc[returnKeyPress], 1);
      send_event(fd, EV_SYN, SYN_REPORT, 0);
      send_event(fd, EV_KEY, abc[returnKeyPress], 0);
      send_event(fd, EV_SYN, SYN_REPORT, 0);
      
	}

	close(fd);

     return 0;
}