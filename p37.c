/**********************************Header Files********************************/
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
/*********************************End of Block******************************/

/***************************Defination of Opcodes**************************/
#define BUF_SIZE 516
#define TFTP_OPCODE_RRQ    1
#define TFTP_OPCODE_WRQ    2
#define TFTP_OPCODE_DATA   3
#define TFTP_OPCODE_ACK    4
#define TFTP_OPCODE_ERROR  5
#define TFTP_TRANSFER_MODE "octet"
/*****************************End of Block*****************************/

void handle_tftp (int , struct sockaddr * , int , char *) ;

void handle_tftp(int socketClient , struct sockaddr *server , int serverLength , char *fileName) {

  /***************************Declaration of Local Variables***********************/
  char buffer[BUF_SIZE] ;
  char *p = buffer ;
  short int opcode ;
  short int blockCount ;
  struct sockaddr_in destServer ;
  socklen_t destServerLength ;
  int load , count ;
  /*****************************End of Block********************************/

  opcode = htons(TFTP_OPCODE_RRQ) ;    // Read request opcode from human rewadable format to network format short
  memcpy(p , &opcode , sizeof(opcode)) ; //copy into p for 1st 2 bytes
  p = p + 2 ;
  p = strcpy(p , fileName) ;               //copying filename to the string
  p = p + strlen(fileName) + 1 ;            // adding 1 for \n
  p = strcpy(p , TFTP_TRANSFER_MODE) ;       //copying mode
  p = p + strlen(TFTP_TRANSFER_MODE) + 1 ;    //adding 1 for \n
  load = p - buffer ;

  if ( (sendto(socketClient , buffer , load , 0 , server , serverLength)) == -1) {        //sending data from buffer to server
    perror("Sending Fault\n") ;
    exit(1) ;
  }

  do {

    destServerLength = sizeof(struct sockaddr_in) ;

    if ( (count = recvfrom(socketClient , buffer , BUF_SIZE , 0 , (struct sockaddr *)&destServer , &destServerLength)) == -1) { //Receiving Data from Destination Server
      perror("receiveing error\n") ;
      exit(1) ;
    }

    memcpy(&opcode , buffer , sizeof(short)) ; //copying 2 bytes of opcode
    memcpy(&blockCount , buffer + 2 , sizeof(short)) ; //copying 2 bytes of block Number

    opcode = ntohs(opcode) ;
    blockCount = ntohs(blockCount) ;

    switch (opcode) {

      case TFTP_OPCODE_ERROR :
                                perror("ERROR in transmission of messages\n") ;
                                exit(1) ;
                                break ;

      case TFTP_OPCODE_DATA :
                                if (write(1 , buffer + 4, count-4 ) == -1) {
                                  perror("Writing error\n") ;
                                  exit(1) ;
                                }
    }

  } while (count == BUF_SIZE) ;

  return ;

}

int main(void) {

  int socketClient , addInfo ;
  struct addrinfo hints ;
  struct addrinfo *results , *server , *rp ;
  char *fileName = "bar.txt" ;

  hints.ai_family = AF_INET ;          //Usage of IPv4
  hints.ai_socktype = SOCK_DGRAM ;      // Usage of UDP
  hints.ai_protocol = 0 ;

  if ( (addInfo = getaddrinfo("localhost" , "tftp" , &hints , &results)) == -1) {       //Using localhost server and tftp service
    perror("Getting address\n") ;
    exit(1) ;
  }

  server = NULL;
  rp = results;
  while (rp != NULL) {
    socketClient = socket(results->ai_family , results->ai_socktype , results->ai_protocol) ;  //Creation of Client
    if (-1 != socketClient) {
      server = rp;
      rp = NULL;
    } else {
    printf("Connection failed\n") ;
    rp = rp->ai_next ;
    }
  }

  handle_tftp(socketClient , server->ai_addr , server->ai_addrlen , fileName) ;

  freeaddrinfo(results) ;    //Freeing the memory assigned to result structure

  return EXIT_SUCCESS ;
}
