#include <stdlib.h>
#include <stdio.h>
#include <signal.h> /*for signal() and raise()*/
#include <unistd.h>

/* ignore_stop.c */
int main(){
  //ignore SIGSTOP ?
  signal(SIGSTOP, SIG_IGN);
  //infinite loop
  while(1);
}

