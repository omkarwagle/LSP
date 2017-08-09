/*************************************Header Files*****************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
/*******************************End of Block********************************/

#define PORT_ADDRESS 8000
#define BUF_SIZE 1024

int handle_connection(int , int) ;
void rot13(char * , char * , int) ;

int main(void) {

  /*******************Declaration of Local Variables**************************/
  int socketServer , socketClient , i ;
  struct sockaddr_in server , client ;
  fd_set activeClient , clientCopy ;
  socklen_t clientLength ;
  /*********************End of Block**************************/

  FD_ZERO (&activeClient) ;  //Initialising fd_set to zero
  FD_ZERO (&clientCopy) ;     //Initialising fd_set to zero

  if ( (socketServer = socket(AF_INET , SOCK_STREAM , 0)) == -1) {           //Creation of socket
    perror("Error in creating socket\n") ;
    exit(1) ;
  }

  server.sin_family = AF_INET ;                    //Usage of IPv4
  server.sin_addr.s_addr = htonl(INADDR_ANY) ;      // Display on any address
  server.sin_port = htons(PORT_ADDRESS) ;

  if (bind(socketServer , (struct sockaddr *)&server , sizeof(server)) == -1) {      //Binding Server to Port
    perror("Error in Binding\n") ;
    exit(1) ;
  }

  if (listen(socketServer , 5) == -1) {      //Ready to take connections
    perror("Error in Listening\n") ;
    exit(1) ;
  }
  printf("Listening to Port %d\n" , PORT_ADDRESS) ;

  FD_SET(socketServer , &activeClient) ;         //Setting activeClient with file descriptor socketDerver

  while (1) {

    memcpy(&clientCopy , &activeClient , sizeof(activeClient)) ;      //Creating a copy of value of activeClient

    select(FD_SETSIZE , &clientCopy , NULL , NULL , NULL) ;         //Selection of File Descriptors

    if (FD_ISSET(socketServer , &clientCopy)) {              //Checking whether socketServer and clientCopy has same value

      clientLength = sizeof(client) ;
      if ( (socketClient = accept(socketServer , (struct sockaddr *)&client , &clientLength)) == -1) {  //Accepting connections from clients
        perror("Error in accepting the connections\n") ;
        exit(1) ;
      }

      FD_SET(socketClient , &activeClient) ;   //Setting activeClient with new value of Client
      printf("Got a new connection from the Client %d\n" , client.sin_addr.s_addr) ;
    }

      for (i = 3; i < FD_SETSIZE ; i++) {
        if (i != socketServer) {
          if (FD_ISSET(i , &clientCopy)) {    //checking whether value matches clientCopy
            if (handle_connection(i , i) == -1) {
              printf("Conection Terminated\n") ;
              close(i) ;
              FD_CLR(i , &clientCopy) ;
            }
          }
        }
      }
    }

  return EXIT_SUCCESS ;
}

int handle_connection(int input, int output) {
  char inputBuffer[BUF_SIZE];
  char outputBuffer[BUF_SIZE];
  int readSize;

  if( (readSize=read(input, inputBuffer, BUF_SIZE)) < 1) {
    return -1;
  }
  rot13(inputBuffer, outputBuffer, readSize);

  if(write(output, outputBuffer, readSize) < 1) {
    return -1;
  }
  return 0;
}

void rot13(char *input, char *output, int length) {

  int i ;

  length = length - 2;
  while(length--) {

    i = (int) (*input + 13) ;
    if (i > 122) {
      i -= 26 ;
    }
    else if ( (i > 90) && (i < 97) ) {
      i -= 26 ;
    }

    *output = (char)i ;
    input++;
    output++;
  }
  *output++ = *input++;      //addition of new line
  *output = *input;
  return;
}
