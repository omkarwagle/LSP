/************************************Header Files***********************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*********************************End of Block**********************************/

int main(void) {

  /************************Declaration of Local Variables***********************/
  pid_t parent , child ;
  int i ;
  /******************************End of Block*********************************/

  /***************************Creation of Child Process**************************/
  if((child = fork()) == -1) {
    perror("ERROR!!!!!\n") ;
    exit(1) ;
  }
  /*********************************End of Block********************************/

  /*****************************Creating Parent and child PID***************************/
  if(child) {
  parent = getpid() ; // Generating Parent PID
  for(i = 0 ; i < 100000 ; i++) {
      printf("Parent PID : %d\n" , parent) ;
    }
  }

  else {
  child = getpid() ; //Generating Child PID
  for(i = 0 ; i < 100000 ; i++) {
      printf("Child PID : %d\n" , child) ;
    }
  }
  /*************************************End of Block*********************************/

  return EXIT_SUCCESS;
}
