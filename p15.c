/*********************************Header Files*************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
/*******************************End of Block**************************/

int main(int argc , char *argv[]) {

  /****************************Declaration of Local Variable*****************************/
  char opt ;
  extern int optind , optopt ;
  extern char *optarg ;
  char *fOpt ;
  int CFlag = 0, VFlag = 0 , BFlag = 0, FFlag = 0, i, j ;
  /*********************************End of Block*************************************/

  while((opt = getopt(argc , argv , "cvb:f:")) != -1) { //Checking for options

    switch(opt) {

    case 'c' : CFlag = 1 ;
               break ;

    case 'v' : VFlag = 1 ;
               break ;

    case 'b' : BFlag = 1 ;
               optopt = atoi(optarg) ;
               break ;

    case 'f' : FFlag = 1 ;
               fOpt = (char *)malloc(strlen(optarg)*sizeof(char)) ;
               strcpy(fOpt , optarg) ;
               break ;

    default :
               printf("No Such Option\n") ;
    }
  }

    if(CFlag) {
      printf("option c has been called\n") ;
    }
    if(VFlag) {
      printf("option v has been called\n") ;
    }
    if(BFlag) {
      printf("option b has been called %d\n" , optopt) ;
    }
    if(FFlag) {
      printf("option f has been called %s\n" , fOpt) ;
    }

    i = optind ;
    j = argc - optind ;

    while(j) {
      printf("Number of non argument : %s\n" , argv[i]) ;
      i++ ;
      j-- ;

    }

    free(fOpt) ;


  return 0;
}
