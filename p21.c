/*********************************Header Files**********************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
/**********************************End of Block******************************/

int main(void) {

  /******************************Declaration of Local Variables************************/
  pid_t parent , child ;
  int status , i ;
  /**********************************End of Block*********************************/

  /********************************Creating a Child Process****************************/
  if((child = fork()) == -1) {
    perror("ERROR!!!!!\n") ;
    exit(1) ;
  }
  /***********************************End of Block**********************************/

  if(child) {
    parent = getpid() ;
    printf("Parent PID : %d\n" , parent) ;
    wait( &status ) ; //Putting Parent process in wait condition

    if(WIFEXITED(status)) {
      printf("Child Exited normally : %d\n" , WEXITSTATUS(status)) ;
    }

    if(WIFSIGNALED(status)) {
      printf("Killed by signal no. %d\n" , WTERMSIG(status)) ;
    }
  }
  else {
    child = getpid() ;
    i = 20 ;
    while(i) {
      printf("Child PID : %d\n" , child) ; // Operates when parent process has stopped
      sleep(1) ;
      i-- ;
    }
  }

  return EXIT_SUCCESS;
}
