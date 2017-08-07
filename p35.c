/***************************************Header Files******************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <time.h>
/************************************End of Block*******************************/

#define BUFSIZE 1024

int main(void) {

  /************************Declaration of local Variables*************************/
  struct addrinfo hints ;
  struct addrinfo *results ;
  int socketClient , addInfo , count , connectServer ;
  char buf[BUFSIZE] ;
  /*******************************End of Block********************************/

  memset(&hints , 0 , sizeof(struct addrinfo)) ;
  hints.ai_socktype = SOCK_STREAM ;       //TCP Protocol
  hints.ai_family = AF_INET ;           //Either work with IPv4 or IPv6
  hints.ai_protocol = 0 ;

  if ( (addInfo = getaddrinfo("localhost" , "rot13" , &hints , &results)) == -1) { //get host and server name
    perror("ERROR in getting address of host and service\n") ;
    exit(1) ;
  }

  socketClient = socket(results->ai_family , results->ai_socktype , results->ai_protocol) ;  //Creation of Client
  if (-1 == socketClient) {
    perror("Creation of Client Error\n") ;
    exit(1) ;
  }

  connectServer = connect(socketClient , (struct sockaddr *)results->ai_addr , results->ai_addrlen) ; //Connection of client with the Server
  if (-1 == connectServer) {
    perror("Connection Time Out\n") ;
    exit(1) ;
  }

  freeaddrinfo(results) ;    //Freeing the memory assigned to result structure

  while (1) {

    count = 0 ;
    memset(&buf , 0 , BUFSIZE) ;            //Clearing Buffer before every use

    if ( (count = read(0 , buf , BUFSIZE)) == -1) {         //reading from keyboard to buffer
      perror("Read1\n") ;
      exit(1) ;
    }
    if (write(socketClient , buf , count) == -1) {          //writing to client
      perror("Write1\n") ;
      exit(1) ;
    }

    sleep(2) ;

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
