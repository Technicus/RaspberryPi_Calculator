// Another way to get non-blocking keyboard input is to open the device file and read it!
// 
// You have to know the device file you are looking for, one of /dev/input/event*. You can run cat /proc/bus/input/devices to find the device you want.
// 
// This code works for me (run as an administrator).
// http://stackoverflow.com/questions/448944/c-non-blocking-keyboard-input

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>

int main(int argc, char** argv)
{
   int fd, bytes;
   struct input_event data;
   
   const char *pDevice = "/dev/input/event4";
   
   // Open Keyboard
   fd = open(pDevice, O_RDONLY | O_NONBLOCK);
   if(fd == -1)
   {
      printf("ERROR Opening %s\n", pDevice);
      return -1;
   }
   
   while(1)
   {
      // Read Keyboard Data
      bytes = read(fd, &data, sizeof(data));
      if(bytes > 0)
      {
         printf("Keypress value=%x, type=%x, code=%x\n", data.value, data.type, data.code);
      }
      else
      {
         // Nothing read
         sleep(1);
      }
   }
   
   return 0;
}