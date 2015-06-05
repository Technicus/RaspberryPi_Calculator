#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */

int main ()
{
   int pid;
   printf("Hello Worldn");
   pid = fork();
   
   if(pid != 0)
      printf("I'm the Father and my son's PID is %dn",pid);
   else
      printf("I'm the Sonn");
   
   printf("Goodbye Cruel Worldn");
}

int main ()
{
   int pid, status;
   
   if(fork())
   {
      printf("I'm the Father, and waitingn");
      pid = wait(&status);
      printf("I'm the Father :n - my son's PID is %dn - my son's exit status is %dn", pid, status);
   }else{
      printf("I'm the Son, and sleepingn");
      sleep(1);
      printf("I'm the Son, and exitingn");
      exit(0);
   }
   
   printf("Goodbye Cruel Worldn");
}

int main()
{
    /*Spawn a child to run the program.*/
    pid_t pid=fork();
    if (pid==0) { /* child process */
        static char *argv[]={"echo","Foo is my name.",NULL};
        execv("/bin/echo",argv);
        exit(127); /* only if execv fails */
    }
    else { /* pid!=0; parent process */
        waitpid(pid,0,0); /* wait for child to exit */
    }
    return 0;
}