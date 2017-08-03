/************************************Header Files*************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <limits.h>
#include <string.h>
/************************************End of Block*************************************/

int readDirectory(char *) ; //Function Declaration

/************************Declaration of Global Variables**********************/
DIR *d ;
struct dirent *info ;
struct stat sb ;
struct tm *t ;
int i = 0 ;
time_t timer ;
int hist[24] ;
char *originalPath = "/home/omkarwagle/LSP/p30";
/******************************End of Block***********************************/

int main(void) {

  char getDirectory[200] ;

  d = opendir(originalPath) ; //opening of original path directory
  chdir(originalPath) ; //changing directory to current directory
  while ( (info = readdir(d)) != NULL) {
    stat(info->d_name , &sb) ;
    if(info->d_name[0] == '.') {   //avoiding hidden files
      continue ;
    }

    if (S_ISREG(sb.st_mode)) {
      timer = time(NULL) ;
      t = localtime(&sb.st_mtime) ;
      printf("Hours : %d\n" , t->tm_hour) ;
      hist[t->tm_hour]++ ; //creating a histogram record
    }

      if(S_ISDIR(sb.st_mode)) { //Modifying pathname
        strcpy(getDirectory , originalPath) ;
        strcat(getDirectory , "/") ;
        strcat(getDirectory , info->d_name) ;
        readDirectory(getDirectory) ;
      }
    }

    for(i = 0;i < 24 ; i++){
      printf("Hour %d : %d\n" , i , hist[i]) ;
    }

  closedir(d) ;

  return EXIT_SUCCESS ;
}

int readDirectory(char *getDirectory) {

  /**************************Declaration of Local Variables*************************/
  DIR *insideDirectory ;
  struct dirent *direct ;
  struct stat sb1 ;
  struct tm *t1 ;
  char fullName[100] ;
  /*******************************End of Block*********************************/

  chdir(getDirectory) ;
  insideDirectory = opendir(getDirectory) ;
  strcpy(fullName , getDirectory) ;
  printf("Name : %s\n" , fullName) ;
  stat(fullName , &sb1) ;

  if(S_ISREG(sb1.st_mode)) {            //checking for regular files
    t = localtime(&sb.st_mtime) ;
    printf("Hours : %d\n" , t->tm_hour) ;
    hist[t->tm_hour]++ ;
    return 0 ;
  }

  while ( (direct = readdir(insideDirectory)) != NULL) {
    stat(direct->d_name , &sb1) ;
    printf("%s\n" , direct->d_name) ;

    if(direct->d_name[0] == '.') {
      continue ;
    }

    if (S_ISREG(sb1.st_mode)) {         //checking for regular files
      t1 = localtime(&sb1.st_mtime) ;
      printf("File : %s\n" , direct->d_name) ;
      printf("Hours : %d\n" , t1->tm_hour) ;
      hist[t1->tm_hour]++ ;
    }

    if (S_ISDIR(sb1.st_mode) && direct != NULL) {          //checking for directories
      strcat(fullName , "/") ;
      strcat(fullName , direct->d_name) ;
      readDirectory(fullName) ; //calling function recursively
    }
  }

  return 0 ;
}
