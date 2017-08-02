/***********************************Header Files********************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
/***********************************End of Block********************************/

int main(void){

  /***********************Declaration of Local Variables*************************/
  struct stat buf ;
  struct tm *t ;
  char ptr[100];
  time_t timer ;
  /********************************End of Block**********************************/

  /**************************Displaying Time with ctime()************************/
  stat("./p16.cbp" , &buf) ;
  printf("Actual Time : %s\n" , ctime(&buf.st_atime)) ;
  printf("Modified Time : %s\n" , ctime(&buf.st_mtime)) ;
  printf("Changed Time : %s\n" , ctime(&buf.st_ctime)) ;
  /*******************************End of Block***********************************/

  /**********************Displaying Time with strftime()**************************/
  timer = time(NULL) ;
  t = localtime(&timer) ;
  if(t == NULL) {
    perror("ERROR!!!!\n") ;
    exit(1) ;
  }

  strftime(ptr , 100 , "%A %d %B %Y" , t) ; // Displays day , date , month , year
  printf("%s\n" , ptr) ;
  printf("%s\n" , ctime(&timer)) ;
  /******************************End of Block************************************/

  return 0;
}
