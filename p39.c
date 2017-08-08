/************************************Header Files*********************************/
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <signal.h>
#include <time.h>
/********************************End of Block************************************/

#define PORT_ADDRESS 8000
#define BUF_SIZE 1024

void handle_connection(int , int) ;
void rot13(char * , char *) ;

int main(void) {

  int socketServer , fd ;
  struct sockaddr_in server , client ;

  if ( (socketServer = socket(AF_INET , SOCK_STREAM , 0)) == -1) {          //Creation of Socket
    perror("Error in creating socket\n") ;
    exit(1) ;
  }

  server.sin_family = AF_INET ;           //Usage of IPv4
  server.sin_addr.s_addr = htonl(INADDR_ANY) ;      //Usage of any address
  server.sin_port = htons(PORT_ADDRESS) ;    // assigning 8000 port

  if (bind(socketServer , (struct sockaddr *)&server , sizeof(server)) == -1) {   //Binding Server to port 8000
    perror("Error in binding\n") ;
    exit(1) ;
  }

  if (listen(socketServer , 5) == -1) {         // Ready to accept connections
    perror("Error in listening\n") ;
    exit(1) ;
  }
  printf("Listening to port %d\n" , PORT_ADDRESS) ;

  signal(SIGCHLD , SIG_IGN) ;        //Avoiding Zombies

  while (1) {

    if ( (fd = accept(socketServer , (struct sockaddr *)&client , (socklen_t *)&client)) == -1) {     //Accepting client connections
      perror("Error in acceptance\n") ;
      exit(1) ;
    }

    if (fork() == 0) {        // Creation of Child Process

      close(socketServer) ;    // Close Server
      printf("Got a New Connection\n") ;

      handle_connection(fd , fd) ;
      close(fd) ;
      printf("Connection Terminated\n") ;

      return 0 ;
    }
  }

  return EXIT_SUCCESS ;
}

void handle_connection(int input , int output) {

  char inputBuffer[100] ;
  char outputBuffer[100] ;

    while (read(input , &inputBuffer , 1) > 0) {                   //Reading Byte by Byte
       rot13(inputBuffer , outputBuffer) ;
      if(*outputBuffer == 23 || *outputBuffer == 26 ) {
        continue ;
      }
      write(output , &outputBuffer , 1) ;       //Writing byte by byte
    }

}

void rot13(char *textInput , char *textOutput) {

  int i = 0 ;
  char c ;

  while (*(textInput + i)) {
    c = *(textInput + i) + 13 ;      //Incrementing the given character by 13 as in rot13 format
    if (c > 122) {
      c = c - 26 ;
    }
    else if (c > 90 && c < 97){
      c -= 26 ;
    }
    *(textOutput + i) = c ;
    i++ ;
  }
}
