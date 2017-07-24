#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define FLAGS O_WRONLY | O_CREAT | O_EXCL | O_TRUNC
#define PERMISSION S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH

int main()
{
    /************Declaration of local variables************/
    int fd , blockcount, blocksize , wr ;

    /** Opening of file with Low level IO**/
    fd = open ("bufio", FLAGS , PERMISSION);
    if (fd == -1) {
        perror ("ERROR!!!!\n") ;
    }

    /**Taking input from the user**/
    printf ( "Enter the number of times of buffer to get printed : \n");
    scanf ("%d", &blockcount );
    printf("Enter blocksize : ");
    scanf("%d", &blocksize );

    char buf[blocksize];

    while ( blocksize ) {
     wr = write (fd,buf,blocksize) ;
     blocksize--;
    }

    return 0;
}
