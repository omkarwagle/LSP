/*************************************Header Files***************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
/***********************************End of Block****************************************/

int main(void){

  /******************************Declaration of Local variable***************************/
  DIR *d ;
  struct dirent *details ;
  struct stat buf ;
  char c;

  /********************************End of Block***********************************/
  d = opendir("..") ; //Opening Current Directory
  chdir("..");
  while((details = readdir(d)) != NULL) {

  stat(details->d_name , &buf) ; // assigning path name to stat structure

  /**********************************Checking of File Type******************************/
  if(S_ISREG(buf.st_mode)) {
    c = '-' ;
  }
  else if(S_ISDIR(buf.st_mode)) {
    c = 'd' ;
  }
  else if(S_ISCHR(buf.st_mode)) {
    c = 'c' ;
  }
  else if(S_ISBLK(buf.st_mode)) {
    c= 'b' ;
  }
  else if(S_ISFIFO(buf.st_mode)) {
    c = 'p' ;
  }
  else if(S_ISLNK(buf.st_mode)) {
    c = 'l' ;
  }
  else if(S_ISSOCK(buf.st_mode)) {
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
  printf("  %s\n" , details->d_name) ;
}
  closedir(d) ;
  return 0;
}
