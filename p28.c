/***************************************Header Files*************************/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
/***********************************End of Block******************************/

/***************************Signal Handler Function***************************/
void siginthandler(int sig) {

  printf("Interuppt Handler\n") ;
  return ;
}
/*********************************End of Block********************************/

int main(void)
{
  /*******************************Local Variables******************************/
  sigset_t sigmask ;
  struct sigaction action ;
  char buf[100000] ;
  ssize_t readFile ;
  int p[2] ;
  /*******************************End of Block*********************************/

  /*******************Defining Signal Handler***************************/
  action.sa_handler = siginthandler ;
  sigemptyset(&action.sa_mask) ;
  action.sa_flags = SA_RESTART ;
  sigaction(SIGINT , &action , NULL) ; //SIGINT to be handled
  /*****************************End of Block*****************************/

  if(pipe(p) == -1) {               // Creating Pipe
    perror("ERROR!!!!!\n") ;
    exit(1) ;
  }
  sigemptyset(&sigmask) ;
  sigaddset(&sigmask , SIGINT) ;
  dup2(0 , p[0]) ;  // Creating a copy of stdin in p[0]

  while(1) {
    if((readFile = read(p[0] , &buf , 1000)) == -1) { //read input form std input
      perror("ERROR!!!!!\n") ;
      exit(1) ;
    }

  printf("%lu bytes , %s number of bytes\n" , readFile , buf) ;
  }

  return EXIT_SUCCESS ;
}
