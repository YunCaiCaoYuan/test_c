/*ingore_sigint.c*/
#include <signal.h>
#include <sys/signal.h>

void nothing(int signum){ /*DO NOTHING*/ }

int main(){
  signal(SIGINT, nothing);
  while(1);
}

/*
int main(){
  // using SIG_IGN
  signal(SIGINT, SIG_IGN);
  while(1);
}
*/
