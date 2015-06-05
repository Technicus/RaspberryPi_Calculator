// Calculator example using C code
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
//#include "../include/conio.h"
#include <math.h>
#include <stdlib.h>

#define KEY "Enter the calculator Operation you want to do:"

char getch(){
   /*#include <unistd.h>   //_getch*/
   /*#include <termios.h>  //_getch*/
   char buf=0;
   struct termios old={0};
   fflush(stdout);
   if(tcgetattr(0, &old)<0)
      perror("tcsetattr()");
   old.c_lflag&=~ICANON;
   old.c_lflag&=~ECHO;
   old.c_cc[VMIN]=1;
   old.c_cc[VTIME]=0;
   if(tcsetattr(0, TCSANOW, &old)<0)
      perror("tcsetattr ICANON");
   if(read(0,&buf,1)<0)
      perror("read()");
   old.c_lflag|=ICANON;
   old.c_lflag|=ECHO;
   if(tcsetattr(0, TCSADRAIN, &old)<0)
      perror ("tcsetattr ~ICANON");
   printf("%c\n",buf);
   return buf;
}

// Function prototype declaration
void addition();
void subtraction();
void multiplication();
void division();
void modulus();
void power();
int factorial();
void calculator_operations();

// Start of Main Program
int main()
{
    int X=1;
    char Calc_oprn;

    int pid, status;
    
    if(fork())
    {
       printf("I'm the Father program.");
       //pid = wait(&status);
       //printf("I'm the Father :n - my son's PID is %dn - my son's exit status is %dn", pid, status);
    }else{
       printf("I'm the Son program.");
       sleep(1);
       static char *argv[]={"SimpleCalculator",".",NULL};
       execv("./SimpleCalculator",argv);
    }
    

    // Function call 
    calculator_operations();

    while(X)
    {
        printf("\n");
        printf("%s : ", KEY);

        Calc_oprn=getch();

        switch(Calc_oprn)
        {
            case '+': addition();
                      break;

            case '-': subtraction();
                      break;

            case '*': multiplication();
                      break;

            case '/': division();
                      break;

            case '?': modulus();
                      break;

            case '!': factorial();
                      break;

            case '^': power();
                      break;

            case 'H':
            case 'h': calculator_operations();
                      break;

            case 'Q':
            case 'q': exit(0);
                      break;
            case 'c':
            case 'C': system("cls");
                      calculator_operations();
                      break;

            default : system("cls");

    printf("\n**********You have entered unavailable option");
    printf("***********\n");
    printf("\n*****Please Enter any one of below available ");
    printf("options****\n");
                      calculator_operations();
        }
    }
}

//Function Definitions

void calculator_operations()
{
    //system("cls");  use system function to clear 
    //screen instead of clrscr();
    printf("\n             Welcome to C calculator \n\n");

    printf("******* Press 'Q' or 'q' to quit ");
    printf("the program ********\n");
    printf("***** Press 'H' or 'h' to display ");
    printf("below options *****\n\n");
    printf("Enter 'C' or 'c' to clear the screen and");
    printf(" display available option \n\n");

    printf("Enter + symbol for Addition \n");
    printf("Enter - symbol for Subtraction \n");
    printf("Enter * symbol for Multiplication \n");
    printf("Enter / symbol for Division \n");
    printf("Enter ? symbol for Modulus\n");
    printf("Enter ^ symbol for Power \n");
    printf("Enter ! symbol for Factorial \n\n");
}

void addition()
{
    int n, total=0, k=0, number;
    printf("\nEnter the number of elements you want to add:");
    scanf("%d",&n);
    printf("Please enter %d numbers one by one: \n",n);
    while(k<n)
    { 
        scanf("%d",&number);
        total=total+number;
        k=k+1;
    }
    printf("Sum of %d numbers = %d \n",n,total);
}

void subtraction()
{ 
    int a, b, c = 0; 
    printf("\nPlease enter first number  : "); 
    scanf("%d", &a); 
    printf("Please enter second number : "); 
    scanf("%d", &b); 
    c = a - b; 
    printf("\n%d - %d = %d\n", a, b, c); 
}

void multiplication()
{
    int a, b, mul=0; 
    printf("\nPlease enter first numb   : "); 
    scanf("%d", &a); 
    printf("Please enter second number: "); 
    scanf("%d", &b);
    mul=a*b;
    printf("\nMultiplication of entered numbers = %d\n",mul);
}

void division()
{
    int a, b, d=0; 
    printf("\nPlease enter first number  : "); 
    scanf("%d", &a); 
    printf("Please enter second number : "); 
    scanf("%d", &b);
    d=a/b;
    printf("\nDivision of entered numbers=%d\n",d);
}

void modulus()
{
    int a, b, d=0; 
    printf("\nPlease enter first number   : "); 
    scanf("%d", &a); 
    printf("Please enter second number  : "); 
    scanf("%d", &b);
    d=a%b;
    printf("\nModulus of entered numbers = %d\n",d);
}

void power()
{
    double a,num, p;
    printf("\nEnter two numbers to find the power \n");
    printf("number: ");
    scanf("%lf",&a);

    printf("power : ");
    scanf("%lf",&num);

    p=pow(a,num);

    printf("\n%lf to the power %lf = %lf \n",a,num,p);
}

int factorial()
{
    int i,fact=1,num;

    printf("\nEnter a number to find factorial : ");
    scanf("%d",&num);

    if (num<0)
    {
        printf("\nPlease enter a positive number to");
        printf(" find factorial and try again. \n");
        printf("\nFactorial can't be found for negative");
        printf(" values. It can be only positive or 0  \n");
        return 1;
    }               

    for(i=1;i<=num;i++)
    fact=fact*i;
    printf("\n");
    printf("Factorial of entered number %d is:%d\n",num,fact);
    return 0;
}
