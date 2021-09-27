#include <stdlib.h>
#include <stdio.h>
#include <signal.h> /*for signal() and raise()*/
#include <unistd.h>

/*signal_errorcheck.c*/
int main(){
  //ignore SIGSTOP ?
  if( signal(SIGKILL, SIG_IGN) == SIG_ERR){
    perror("signal");;
    exit(1);
  }
  //infinite loop
  while(1);
}

