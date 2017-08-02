#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

int count ;

void siginthandler(int sig) {
  count = 0 ;
  return ;
}
int main()
{
  sigset_t sigmask ;
  struct sigaction action ;

  action.sa_handler = siginthandler ;
  sigemptyset(&action.sa_mask) ;
  action.sa_flags = SA_RESTART ;
  sigaction(SIGINT , &action , NULL) ;

  action.sa_handler = SIG_IGN ;
  sigaction(SIGQUIT , &action , NULL) ;
  sigaction(SIGTERM , &action , NULL) ;

  sigemptyset(&sigmask) ;
  sigaddset(&sigmask , SIGINT) ;

  while(1) {

    sleep(1) ;
    printf("Count : %d\n" , count) ;
    sigprocmask(SIG_BLOCK , &sigmask , NULL) ;
    count++;
    sigprocmask(SIG_UNBLOCK , &sigmask , NULL) ;

  }


  return EXIT_SUCCESS;
}
