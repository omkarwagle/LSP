/*********************************Header Files*****************************/
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
/***************************End of Block***************************/

#define BUF_SIZE 1024
#define PORT_ADDRESS 8010

int main(void) {

  /**********************Declaration of Local Variables**************************/
  int socketServer ;
  struct sockaddr_in server , client ;
  socklen_t  serverLength , clientLength ;
  int yes = 1 ;
  ssize_t count ;
  char buffer[BUF_SIZE] ;
  /**********************End of Block**********************************/

  if ((socketServer = socket(AF_INET , SOCK_DGRAM , 0)) == -1) {      // creation of socket
    perror("ERROR in Socket\n") ;
    exit(1) ;
  }

  if ( (setsockopt(socketServer , SOL_SOCKET , SO_BROADCAST , (char *)&yes , sizeof(yes))) == -1) {    //Broadcasting condition
    perror("ERROR in Broadcasting\n") ;
    exit(1) ;
  }

  if( (setsockopt(socketServer , SOL_SOCKET , SO_REUSEPORT , (char *)&yes , sizeof(yes))) == -1) {    //Permission to reuse the port
    perror("ERROR in reusing port\n") ;
    exit(1) ;
  }

  server.sin_family = AF_INET ;           //Usage of IPv4
  server.sin_addr.s_addr = htonl(INADDR_ANY) ;        //Assign any address
  server.sin_port = htons(PORT_ADDRESS) ;

  if ((bind(socketServer , (struct sockaddr *)&server , sizeof(server))) == -1) {       //Binding server with port 8000
    perror("ERROR in Binding\n") ;
    exit(1) ;
  }

  if (fork() == 0) {    //Creation of Child Process

    while (1) {

      clientLength = sizeof(struct sockaddr) ;

      if ( (count = recvfrom(socketServer , buffer , BUF_SIZE , 0 , (struct sockaddr *)&client , &clientLength)) == -1) { //Receiving blocks of data from client and storing in buffer
        perror("ERROR in receiving packets\n") ;
        exit(1) ;
      }
      if (write(1 , buffer , count) == -1) {    //Write data in buffer to monitor
        perror("Error in Writing\n") ;
        exit(1) ;
      }
    }
  } else {       //Parent Process

      while (1) {

        serverLength = sizeof(struct sockaddr) ;

        if ( (count = read(0 , buffer , BUF_SIZE)) == -1) {       //Reading from stdin tro buffer
          perror("Error in Reading\n") ;
          exit(1) ;
        }
        server.sin_family = AF_INET;                                //Usage of IPv4
        server.sin_port = htons(PORT_ADDRESS);
        server.sin_addr.s_addr = 0xFFFFFFFF;                        //all addresses

        if ( sendto(socketServer , buffer , count , 0 , (struct sockaddr *)&server , serverLength) == -1) { //send blocks of data to server from buffer
          perror("Error in sending packets to server\n") ;
          exit(1) ;
        }
      }
  }

  return EXIT_SUCCESS ;
}
