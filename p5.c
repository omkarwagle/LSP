#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#define FLAGS O_RDWR | O_CREAT | O_TRUNC
#define PERMISSION S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH
#define EMPLOYEE_NUMBER 3

typedef struct member {
  int id;
  char name[80];
}member;

int main()
{
  member Employee[3] = { {1,"OMKAR"} , {2,"AVINASH"} , {3,"TEJAKIRAN"} };
  int fd , memberSize = sizeof(member) ;
  ssize_t fileWrite;
  off_t SEEK;

  fd = open("datafile.txt" , FLAGS , PERMISSION);
  if( -1 == fd) {
    perror("ERROR!!!!\n");
  }

  fileWrite = write(fd , &Employee[0], memberSize);
  fileWrite = write(fd , &Employee[1], memberSize);
  fileWrite = write(fd , &Employee[2], memberSize);

  if( -1 == fileWrite) {
    perror("ERROR!!!!\n");
  }
  memcpy(( &Employee[EMPLOYEE_NUMBER - 1].name ) , "OM!" , ( sizeof(Employee[EMPLOYEE_NUMBER - 1].name )));

  SEEK = lseek(fd , (EMPLOYEE_NUMBER-1)*memberSize , SEEK_SET);
  if(-1 == SEEK) {
    perror("ERROR!!!!\n");
  }

  fileWrite = write(fd ,&Employee[EMPLOYEE_NUMBER - 1], sizeof(Employee[EMPLOYEE_NUMBER - 1].name ));
  if( -1 == fileWrite ) {
    perror("ERROR!!!!!\n");
  }

}
