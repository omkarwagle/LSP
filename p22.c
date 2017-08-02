/******************************Header Files****************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
/******************************End of Block*****************************/

int main(void) {

  /*********************Declaration of Local Variable*************************/
  int i ;
  char *cmd[] = {"ps" , "ls" , "date" , "ifconfig"} ;
  /**********************End of Block***************************/

  /**********************Chosing Options*******************************/
  printf("Choose option : 1.ps\n2.ls\n3.date\n4.Ifconfig : ") ;
  scanf("%d" , &i) ;
  /*************************End of Block******************************/

  if((i > 0) && (i < 5)) {
    execlp(cmd[i-1] , cmd[i-1] , NULL) ; // Replacing a process image
  }

  return EXIT_SUCCESS ;
}
