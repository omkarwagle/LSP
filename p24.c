/***********************************Header Files*****************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/********************************End of Block******************************/

int main(void){

  /*************************Declaration of Local Variables***********************/
  pid_t parent , child ;
  int p[2] ;
  /******************************End of Block******************************/

  /*************************Creation of pipe*******************************/
  if(pipe(p) == -1) {
    perror("ERROR!!!!\n") ;
    exit(1) ;
  }
  /*****************************End of Block********************************/

  /*******************************Creation of Parent Process*****************************/
  if((child = fork()) == -1) {
    perror("ERROR!!!!\n") ;
    exit(1) ;
  }

  if(child) {

    parent = getpid() ;
    if(dup2(p[0] , 0) == -1) { //relpacing stdin with p[0]
      perror("ERROR\n") ;
      exit(1);
    }
    if(close(p[1]) == -1) {
      perror("ERROR!!!!\n") ;
      exit(1) ;
    }
    printf("Parent PID : %d\n" , parent) ;
    execlp("sort" , "sort" , "-r" , NULL) ;
  }

  else {

    child = getpid() ;
    if(dup2(p[1] , 1) == -1) { //replacing stdout with p[1]
      perror("ERROR!!!!\n") ;
      exit(1) ;
    }

    if(close(p[0]) == -1) {
      perror("ERROR!!!!\n") ;
      exit(1) ;
    }

    printf("Child PID : %d\n" , child) ;
    execlp("ls" , "ls" , "-lt", NULL) ;
  }
  /************************************End of Block*************************************/

  return EXIT_SUCCESS ;
}
