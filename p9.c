/*************************************Header Files***************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
/***********************************End of Block****************************************/

int main(void){

  /******************************Declaration of Local variable***************************/
  struct stat buf ;
  char c;
  char *fileName = "bin" ;
  /********************************End of Block***********************************/

  stat(fileName , &buf) ; // assigning path name to stat structure

  /**********************************Checking of File Type******************************/
  if(S_ISREG(buf.st_mode)) {
    c = '-' ;
  }
  if(S_ISDIR(buf.st_mode)) {
    c = 'd' ;
  }
  if(S_ISCHR(buf.st_mode)) {
    c = 'c' ;
  }
  if(S_ISBLK(buf.st_mode)) {
    c= 'b' ;
  }
  if(S_ISFIFO(buf.st_mode)) {
    c = 'p' ;
  }
  if(S_ISLNK(buf.st_mode)) {
    c = 'l' ;
  }
  if(S_ISSOCK(buf.st_mode)) {
    c = 's' ;
  }
  /***********************************End of Block**********************************/

  /*****************************Checking and printing file permissions****************************/
  printf("%c%c%c%c%c%c%c%c%c%c" , c ,
                                  ((buf.st_mode & S_IRUSR) ? 'r' : '-' ) ,
                                  ((buf.st_mode & S_IWUSR) ? 'w' : '-' ) ,
                                  ((buf.st_mode & S_IXUSR) ? 'x' : '-' ) ,
                                  ((buf.st_mode & S_IRGRP) ? 'r' : '-' ) ,
                                  ((buf.st_mode & S_IWGRP) ? 'w' : '-' ) ,
                                  ((buf.st_mode & S_IXGRP) ? 'x' : '-' ) ,
                                  ((buf.st_mode & S_IROTH) ? 'r' : '-' ) ,
                                  ((buf.st_mode & S_IWOTH) ? 'w' : '-' ) ,
                                  ((buf.st_mode & S_IXOTH) ? 'x' : '-' )) ;

  /********************************End of Block***************************/

  printf("  %lu" , buf.st_size) ; //File Size
  printf("  %s" , ctime(&buf.st_mtime)) ; //Last Modified Time
  printf("  %s\n" , fileName) ;

  return 0;
}
