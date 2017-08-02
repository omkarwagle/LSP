/*******************************Header Files***************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
/*********************************End of Block*****************************/

int main(void) {

  /*********************Declaration of Local Variable************************/
  pid_t parent , child , childppid;
  /******************************End of Block*******************************/

  /*****************************Creation of child Process***********************/
  if((child = fork()) == -1) {
    perror("ERROR!!!!\n") ;
    exit(1) ;
  }
  /********************************End of Block*******************************/

  if(child) {
    parent = getpid() ; // Getting Parent PID
    printf("Parent PID : %d\n" , parent) ;
  }

  else {
  child = getpid() ; //Getting Child PID
  childppid = getppid() ; //Getting child PPID to match with parent PID
  printf("Child PID : %d\n" , child) ;
  printf("Child Parent PID : %d\n" , childppid) ;
  }

  return EXIT_SUCCESS;
}
