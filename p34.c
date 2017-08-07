/*******************************Header Files****************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
/*******************************End of Block******************************/

#define BUFSIZE 1024

int main(void) {

  /****************************Declaration of Local Variables**********************/
  int socketClient ;
  struct sockaddr_in server ;
  struct servent *serverInfo ;
  struct hostent *hostInfo ;
  int count ;
  char buf[BUFSIZE] ;
  /*****************************End of Block********************************/

  hostInfo = gethostbyname("localhost") ;       //giving host a name
  serverInfo = getservbyname("rot13" , "tcp") ;   //invoking rot13 server in/etc/services/

  server.sin_family = AF_INET ;   //IPv4
  memcpy(&server.sin_addr , hostInfo->h_addr , hostInfo->h_length) ;
  server.sin_port = serverInfo->s_port ; //assigning rot13 port ie 8000

  socketClient = socket(AF_INET , SOCK_STREAM , 0) ;            // Creation of client
  if (-1 == socketClient) {
    perror("Client\n") ;
    exit(1) ;
  }

  if ( (connect(socketClient , (struct sockaddr *)&server , sizeof(server))) == -1) {  //connection of client with server (rot13)
    perror("Connection Out\n") ;
    exit(1) ;
  }

  while (1) {

    count = 0 ;
    memset(&buf , 0 , BUFSIZE) ;

    if ( (count = read(0 , buf , BUFSIZE)) == -1) {         //reading from keyboard to buffer
      perror("Read1\n") ;
      exit(1) ;
    }
    if (write(socketClient , buf , count) == -1) {          //writing to client
      perror("Write1\n") ;
      exit(1) ;
    }
    if ( (count = read(socketClient , buf , count)) == -1) {    //reading from client
      perror("Read2\n") ;
      exit(1) ;
    }
    if(write(1 , buf , count) == -1) {      //writing data onto monitor
      perror("Write2\n") ;
      exit(1) ;
    }
  }

  close(socketClient) ;

  return EXIT_SUCCESS ;
}
