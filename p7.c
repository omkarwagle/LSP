/***********************************Header Files****************************************/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
/**********************************End of Header Files**********************************/

/**********************************Symbolic Constants***********************************/
#define FLAG_READWRITE O_RDWR | O_CREAT | O_TRUNC
#define PERMISSION S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH
#define Employee_no 1
/**********************************End of Declaration***********************************/

/**********************************Global Declaration of Structure**********************/
typedef struct member {

  int id;
  char name[80];
} member ;
/*********************************End of Declaraion************************************/

int main(void) {

  /******************************Declaration of Local Variables************************/
  int fileReadWrite ;
  member Employee[3] = {{1 , "Omkar"} , {2 , "Avinash"} , {3 , "ThejaKiran"}} ;
  off_t size ;
  ssize_t fileWrite ;
  /*****************************End of Block******************************************/

  /********************Creating a Source File with error checking********************/
  fileReadWrite = open("fileSource.txt" , FLAG_READWRITE , PERMISSION) ;
  if(fileReadWrite == -1) {
    perror("ERROR!!!!!\n") ;
    exit(1) ;
  }
  /******************************End of Block******************************/

  /**************************Calculation of File Size*********************************/
  size = lseek(fileReadWrite , 0 , SEEK_END) ;
  if(size == -1) {
    perror("ERROR!!!!\n") ;
    exit(1) ;
  }
  /**********************************End of Block*******************************/

  /******************************Creation of Virtual Memory****************************/
  char *textMemory = mmap(NULL , size , PROT_READ | PROT_WRITE , MAP_SHARED , fileReadWrite , 0) ;
  textMemory = "ELEAR" ; // Assigning a string to the virtual Memory
  /************************************End of Block**************************************/
  if(strlen(Employee[Employee_no].name) > strlen(textMemory)) {
  memcpy(&Employee[Employee_no].name , textMemory , strlen(Employee[Employee_no].name)) ;// Copying from Virtual Memory to address of required Structure member
  }
  else {
  memcpy(&Employee[Employee_no].name , textMemory , strlen(textMemory)) ;
  }
  /*************************************Writing with modified data***********************/
  fileWrite = write(fileReadWrite , &Employee[0] , sizeof(Employee[0])) ;
  fileWrite = write(fileReadWrite , &Employee[1] , sizeof(Employee[1])) ;
  fileWrite = write(fileReadWrite , &Employee[2] , sizeof(Employee[2])) ;
  if(fileWrite == -1) {
    perror("ERROR!!!!\n") ;
    exit(1);
  }
  /*************************************End of Block************************************/

  return EXIT_SUCCESS;
}
