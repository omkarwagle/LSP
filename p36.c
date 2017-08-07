/********************************Header Files****************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
/******************************End of Block*****************************/

#define PORT_ADDR 8000         //PreDefined Port Address

void rot13(char *) ;         //Function

int main(void) {

  /************************Declaration of Local Variables*******************/
  int sock , clientFile ;
  struct sockaddr_in6 server , client ;
  char text[10] ;
  /*****************************End of Block****************************/

  sock = socket(AF_INET6 , SOCK_STREAM , 0) ; //Creation of Server Socket
  if (-1 == sock) {
    perror("SOCKET\n") ;
    exit(1) ;
  }

  server.sin6_family = AF_INET6 ; //Usage of IPv6
  server.sin6_addr = in6addr_any ; //Assigning any address
  server.sin6_port = htons(PORT_ADDR) ;

  if (bind(sock , (struct sockaddr *)&server , sizeof(server)) == -1) {  // Binding Server Address
    perror("Binding Issue\n") ;
    exit(1) ;
  }

  if (-1 == listen(sock , 10)) {       //Ready to take connections
    perror("Not ready to Listen\n") ;
    exit(1) ;
  }

  printf("Connection Received from port %d\n" , PORT_ADDR) ;

  while (1) {

    if ((clientFile = accept(sock , (struct sockaddr *)&client , (socklen_t *)&client)) == -1) {  //accepting client conncections
      perror("Accepting Denied\n") ;
      exit(1) ;
    }
    printf("Got a New Connection\n") ;


    while (read(clientFile , &text , 1) > 0) {       //reading byte by byte
      rot13(text) ;
      if (*text == 23 || *text == 26 ) {                              //function call to rot13i
        continue ;
      }
      write(clientFile , &text , 1) ;               //writing byte by byte
    }

    printf("Connection Terminated\n") ;
    close(clientFile) ;                            //termination of client
  }

  return EXIT_SUCCESS ;
}

void rot13(char *text) {

  int i = 0 ;
  char c ;

  while (*(text + i)) {
    c = *(text + i) + 13 ;      //Incrementing the given character by 13 as in rot13 format
    if (c > 122) {
      c = c - 26 ;
    }
    else if (c > 90 && c < 97){
      c -= 26 ;
    }
    *(text + i) = c ;
    i++ ;
  }
}
