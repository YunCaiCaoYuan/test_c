#include <stdlib.h>
#include <stdio.h>
#include <signal.h> /*for signal() and raise()*/

/* hello_loop.c*/
void hello(int signum){
  printf("Hello World!\n");
}

int main(){
  //Handle SIGINT with hello
  signal(SIGINT, hello);

  //loop forever!
  while(1);

}
