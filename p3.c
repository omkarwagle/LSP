#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    char buf[100];
    int fd;

    FILE * WR = fopen ("bar.txt","w");
    if(! WR) {
        perror ("ERROR!!!\n");
    }

    FILE * RD = fopen ("foo.txt","r");
    if(! RD) {
        perror("ERROR!!!!\n");
    }

    while ( fd = fread (buf , 1 , 1 , RD) > 0 ) {
        fd = fwrite (buf , fd , 1 , WR);
    }
    
    return 0;
}
