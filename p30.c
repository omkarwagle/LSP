#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int count ;
char val ;

void sighuphandler(int sig) {

  FILE *fd ;

  if((fd = fopen("reconfile.conf" , "r+")) == NULL) {
    perror("ERROR!!!!!\n") ;
    exit(1) ;
  }
fscanf(fd , " %d %c" , &count , &val) ;

}

int main(void) {

  sigset_t sigmask ;
  struct sigaction action ;
  int i ;
  pid_t parent ;

  action.sa_handler = sighuphandler ;
  sigemptyset(&action.sa_mask) ;
  action.sa_flags = SA_RESTART ;
  sigaction(SIGHUP , &action , NULL) ;

  parent = getpid() ;
  sigemptyset(&sigmask) ;
  sigaddset(&sigmask , SIGHUP) ;

  printf("Process Id : %d\n" , parent) ;
  sighuphandler(1) ;

  while(1) {

  sleep(1);
  sigprocmask(SIG_BLOCK , &sigmask , NULL) ;
  for(i = 0; i<count ; i++) {
    printf("%c",val) ;
  }
  sigprocmask(SIG_UNBLOCK , &sigmask , NULL) ;
  printf("\n") ;

  }

  return EXIT_SUCCESS ;
}
