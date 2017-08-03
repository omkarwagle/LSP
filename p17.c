/* Build histogram of modification hour of files */

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

void processPath(char *) ;
int hist[24] ;

int main(void) {

  int i ;
  char *originalPath = "/home/omkarwagle/LSP" ;

  processPath(originalPath) ;

  for(i = 0 ; i < 24 ; i++) {
      printf("Hour %d : %d\n" , i , hist[i]) ;
    }

  return EXIT_SUCCESS ;
}

void processPath(char *pathName) {

  DIR *d ;
  struct stat sb ;
  struct dirent *info ;
  char path[PATH_MAX] ;
  struct tm *fileTime ;

  d = opendir(pathName) ;
  while( (info = readdir(d)) != NULL) {

    strcpy(path , pathName) ;
    strcat(path , "/") ;
    strcat(path , info->d_name) ;
    stat(path , &sb) ;
    printf("Path : %s\n" , path)  ;

    if(info->d_name[0] == '.') {
      continue ;
    }

    if(S_ISDIR(sb.st_mode)) {
      if(S_ISREG(sb.st_mode) == 0) {
        processPath(path) ;
      }
    }
    else {
      fileTime = localtime(&sb.st_mtime) ;
      hist[fileTime->tm_hour]++ ;
      printf("Time : %d\n" , fileTime->tm_hour) ;
    }
  }

  closedir(d) ;

  return ;
}
