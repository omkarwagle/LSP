#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#define FLAG_fdRead O_RDONLY
#define FLAG_fdWrite O_RDWR | O_CREAT | O_TRUNC
#define PERMISSION S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH

int main(void) {

  /*********Initialisation of local variable*********/
  int fdWrite , fdRead;
  char * addressWrite, *addressRead ;
  off_t SEEK ;
  /*************End of local variable declaration************/

  /********Opening source and Destination File withe error checking*******/
  fdRead = open("dataFileSource.txt" , FLAG_fdRead , PERMISSION);
  if( -1 == fdRead ) {
    perror("ERROR!!!!\n");
    return EXIT_FAILURE ;
  }

  fdWrite = open("dataFileDestination.txt" , FLAG_fdWrite , PERMISSION);
  if( -1 == fdWrite) {
    perror("ERROR!!!!\n");
    return EXIT_FAILURE ;
  }
  /**************End of File Opening Block**************/

  /********Determination of page size********/
  SEEK = lseek( fdRead , 0 , SEEK_END ) ;
  /******End of page size block*******/

  /**************Adjusting the page size*************/
  if(ftruncate( fdWrite , SEEK ) == -1) {  //Truncating the destination to source file size to avoid data loss or garbage data
    perror("ERROR!!!\n") ;
    return EXIT_FAILURE ;
  }
  /**********End of page Size block*************/

  /**************Assigning a memory to Source and Destination File****************/
  addressRead = mmap(NULL , 2 * SEEK , PROT_READ , MAP_SHARED , fdRead , 0 ) ;
  if(addressRead == MAP_FAILED) {
    perror("ERROR!!!!\n");
    return EXIT_FAILURE ;
  }

  addressWrite = mmap( NULL, SEEK , PROT_WRITE | PROT_READ , MAP_SHARED , fdWrite , 0);
  if(addressWrite == MAP_FAILED) {
    perror("ERROR!!!!\n");
    return EXIT_FAILURE ;
  }
  /******************End of Block*******************/

  /**************Memory copying Block**************/
  memcpy(addressWrite , addressRead , SEEK) ;
  /******************End of Block*****************/

  /*************Memory Sync Block***************/
  msync(addressWrite , SEEK , MS_SYNC ) ;
  /*************End of Block*******************/

  return EXIT_SUCCESS ;
}
