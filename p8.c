/**********************************Header Files************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
/**********************************End of Block************************************/

int main(void) {

  struct stat buf;

  stat("main.c" , &buf) ; //Providing pathname to the buffer

  printf("%s\n" , ctime(&buf.st_atime)) ; //access time
  printf("%s\n" , ctime(&buf.st_mtime)) ; //modify time
  printf("%s\n" , ctime(&buf.st_ctime)) ; //change time

  return 0;
}
