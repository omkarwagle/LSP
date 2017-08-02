/**********************************Header files****************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
/*********************************End of Block******************************/

/*******************************ALARM Function*******************************/
void sigalarmHandler(int sig) {

}
/*******************************End of Funtion*******************************/

int main(void) {

  /****************************Local Variables****************************/
  struct sigaction action ;
  char line[50] ;
  int i ;
  /***************************End of Block*******************************/

  /******************************Signal Handler Block*******************************/
  printf("Process PID : %d\n" , getpid()) ;
  action.sa_handler = sigalarmHandler ; //set signal handler
  sigemptyset(&action.sa_mask) ;
  action.sa_flags = 0 ;
  sigaction(SIGALRM , &action , NULL) ; //SIGALRM signal is to be handled
  /*******************************End of Block*********************************/

  while(1) {

    printf("Enter a string : \n") ;
    alarm(5) ; //Setting 5 sec time for alarm
    i = read(0 , &line , 50) ; // raeding input directly from stdin i.e keyboard
    alarm(0) ; // clearing the alarm
    if(-1 == i) {
      printf("NO INPUT\n") ; //if read fails or no input given
    }
    else {
    write(1 , &line , strlen(line)) ; //write entered data to screen
    }
  }

  return EXIT_SUCCESS ;
}
