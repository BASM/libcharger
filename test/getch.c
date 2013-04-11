#include <termios.h>
#include <stdio.h>
#include <unistd.h>

static struct termios old, new;

#define NONBLOCK 1

static void initTermios(int type) 
{
  tcgetattr(0, &old);
  new = old;
  new.c_lflag &= ~(ICANON | ECHO);

  if (type&NONBLOCK) {
    new.c_cc[VMIN]=0;
    new.c_cc[VTIME]=0;
  }else{
    new.c_cc[VMIN]=1;
  }
  tcsetattr(0, TCSANOW, &new);
}

void resetTermios(void) 
{
  tcsetattr(0, TCSAFLUSH, &old);
}

static int doit(int type) 
{
  char ch;
  initTermios(type);
  char b;

  if (!(type&NONBLOCK))
    tcflush(fileno(stdin), TCIOFLUSH);

  ch = read(fileno(stdin), &b, 1);//getchar();
  ch=b;

  if ((type&NONBLOCK))
    tcflush(fileno(stdin), TCIOFLUSH);

  resetTermios();
  return ch;
}

int getch(void) 
{
  return doit(0);
}

int trych(void)
{
  return doit(NONBLOCK);
}
