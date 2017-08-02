/*******************************Header Files****************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
/******************************End of Block*****************************/

int main(void) {

  /*************************Declaration of Local Variables************************/
  struct stat buf;
  DIR *d ;
  struct dirent *details ;
  static int totalSize ;
  /*****************************End of Block*****************************/

  /*************Calculation of Total Size of Current Directory**************/
  d=opendir(".") ;
  stat("." , &buf) ;

  while((details = readdir(d)) != NULL ) {
    totalSize += buf.st_size ;
  }
  /****************************End of Block************************/

  printf("%d\n" , totalSize) ;
  return EXIT_SUCCESS;
}
