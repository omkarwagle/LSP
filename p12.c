/******************************Header Files*************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <limits.h>
/******************************End of Block**************************/

int main(void) {

  /************************Declaration of Local Variables**************************/
  FILE *fd ;
  struct inotify_event *event;
  char buffer[100 * (sizeof(struct inotify_event) + NAME_MAX+1)] ;
  int notifyHandler , watchHandler ;
  int i = 0 ;
  /***************************End of Block****************************/

  if ( (notifyHandler = inotify_init()) == -1) {  // Creating notify instance
    perror("ERROR!!!!\n") ;
    exit(0) ;
  }

  if ( (fd = fopen("monitor.conf" , "r+")) == NULL) { //Creating a target file
    perror("ERROR!!!!\n") ;
    exit(0) ;
  }

  if ((watchHandler = inotify_add_watch(notifyHandler , "monitor.conf" , IN_DELETE_SELF | IN_MODIFY)) == -1) { //creating a watchhandler to check out every changes in targget file
    perror("ERROR!!!!\n") ;
    exit(0) ;
  }

  while (1) {

    if((i = read(notifyHandler , &buffer , sizeof(buffer))) == -1) { //reading from notify instance to buffer
      perror("ERROR!!!!\n") ;
      exit(0) ;
    }

    event = (struct inotify_event  *)buffer; //typecasting buffer data to notify structure type

    if(event->mask & IN_MODIFY) {     //Checking for Modification
      printf("FILE has been modified\n") ;
    }
    if (event->mask & IN_DELETE_SELF) {   // Checking for Deletion
      printf("File has been deleted\n") ;
    }
  }

  return EXIT_SUCCESS ;
}
