/***********************************Header Files*****************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/times.h>
#include <string.h>
#include <unistd.h>
/***********************************End of Block*****************************/

int main(void) {

  /******************************Declaration of Local variable*********************/
  struct tms buf ;
  clock_t begin = clock() ;
  clock_t end ;
  int fd ,  i;
  ssize_t fileWrite ;
  char *textMessage = "Hello World!!!!!\n" ;
  /*********************************End of Block*****************************/

  /**************************Creating a process**************************/
  fd = open("Process.txt" , O_RDWR | O_CREAT , S_IRUSR | S_IWUSR | S_IRGRP ) ;
  for(i = 0 ; i < 1000000 ; i++) {
    if((fileWrite = write(fd , textMessage , strlen(textMessage))) == -1) {
      perror("ERROR!!!!!\n") ;
      exit(1) ;
    }
  }
  close(fd) ;
  /***************************Closing a Process******************************/

  /************************Calculation of Process Time***********************/
  printf("%lu\n" , sysconf(_SC_CLK_TCK)) ;
  times(&buf) ;
  printf("User time : %lu\n" , buf.tms_utime) ;
  printf("System Time : %lu\n" , buf.tms_stime) ;
  printf("Children User Time : %lu\n" , buf.tms_cutime) ;
  printf("System Time for Children : %lu\n" , buf.tms_cstime) ;
  end = clock() ;
  printf("Total Time elapsed : %lu\n" , (end - begin) / CLOCKS_PER_SEC) ;
  printf("Final Clock value : %lu\n" , clock() / CLOCKS_PER_SEC) ;
  /************************End of Block*************************************/

  return 0;
}
