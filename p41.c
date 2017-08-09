/***************************Header Files***************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
/**************************End of Block***************************/

void *child_Thread(void *arg) ;

void *child_Thread(void *arg) {          //Creation of function for pthread_create

  printf("I am the Child Process\n") ;
  sleep(30) ;
  return ((void *)99) ;
}

int main(void) {

  int n , exitStatus ;
  pthread_t child ;

  if ( (n = pthread_create(&child , NULL , child_Thread , "Hello World") == -1)) {          //Creation of Thread
    perror("Error in Creation\n") ;
    exit(1) ;
  }

  printf("I am the parent thread waiting for the child\n") ;
  pthread_join(child , (void **)&exitStatus) ;    //Joining of child Thread
  printf("Child Process with status %d\n" , exitStatus) ;

  return EXIT_SUCCESS ;
}
