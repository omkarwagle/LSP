/*********************************Header Files***************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*******************************End of Block*****************************/

/******************************Function Declaration***************************/
void command (char * , char *) ;
/********************************End of Block******************************/

/****************************Function Defination****************************/
void command (char *cmd , char * attribute) {
  execlp(cmd , cmd , attribute , NULL) ;
}
/*****************************End of Block**********************************/

int main(void) {

  /******************Declaration of Local Variables*************************/
  char * cmd = (char *)malloc(50);
  char * attribute = (char *)malloc(10) ;
  /**************************End of Block***********************************/

  printf("ashish> ") ;
  scanf("%s %s" , cmd , attribute) ;

  command(cmd , attribute) ; // Function Call

  return EXIT_SUCCESS;
}
