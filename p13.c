#include <stdio.h>
#include <stdlib.h>

//extern char **environ ;

int main(int argc , char *argv[]) {

  int i;
  for(i = 1; i < argc ; i++) {
    printf("%s" , argv[i]) ;
  }
  printf("\n") ;
  return 0;
}