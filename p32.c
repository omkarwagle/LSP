/************************************Header Files****************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
/************************************End of Block***************************/

#define PORT_ADDRESS 8000 //Port Number defined

int main(void) {

  /********************Declaration of Local Variables********************/
  int fd , file ;
  char text[100] ;
  struct sockaddr_in server , client ;
  /************************End of Block******************************/

  /******************Creation of server Socket***********************/
  fd = socket(AF_INET , SOCK_STREAM , 0) ;
  if (-1 == fd) {
    perror("ERROR!!!!\n") ;
    exit(1) ;
  }
  /*********************End of Block**********************/

  server.sin_family = AF_INET ; //Usage of IPv4
  server.sin_addr.s_addr = htonl(INADDR_ANY) ;
  server.sin_port = htons(PORT_ADDRESS) ;

  if(bind(fd , (struct sockaddr *)&server , sizeof(server)) == -1) { // Binding socket address
    perror("ERROR!!!!\n") ;
    exit(1) ;
  }

  if((listen(fd , 10)) == -1) { //ready to receive connections
    perror("ERROR!!!!\n") ;
    exit(1) ;
  }
  printf("Listening on port %d\n", PORT_ADDRESS) ;

  while(1) {

    if((file = accept(fd , (struct sockaddr *)&client , (socklen_t *)(&client))) == -1) { //Accept client connection
      perror("ERROR!!!!\n") ;
      exit(1) ;
    }
    printf("Got a new connection!!!!!\n") ;

    while(read(file , &text , 1) > 0) { //read until empty
      write(file , &text , 1) ;
    }

    printf("Connection terminated\n") ;
    close(file) ;
  }

  return EXIT_SUCCESS;
}
