/*********************LOW LEVEL IO**********************/
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#define FLAGS O_WRONLY | O_CREAT | O_TRUNC
#define PERMISSION S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH

int main()
{
    /************Declaration of local variables************/
    int fd , blockcount, blocksize ;
    ssize_t fileWrite;
    double timeDifference ;

    /******Opening of file with Low level IO and checking for error condition*****/
    fd = open ("bufio", FLAGS , PERMISSION);
    if (fd == -1) {
        perror ("ERROR!!!!\n") ;
    }

    /**********Taking input from the user**********/
    printf ( "Enter the number of times of buffer to get printed : \n");
    scanf ("%d", &blockcount );
    printf("Enter blocksize : ");
    scanf("%d", &blocksize );

    char *buf = (char *) malloc (sizeof(char)*blocksize);

    /************Writing of file and Measurement of loop Duration**********/
    clock_t begin = clock(); //initialising begin with current value of clock
    while ( blockcount ) {
     fileWrite = write (fd , buf , blocksize) ;   //writing buffer of size blocksize to file blockcount no of times
     blockcount--;
    }
    free(buf);
    if( -1 == fileWrite ) {
        perror("ERROR!!!!\n");
    }
    clock_t end = clock(); //initialising end with the value of clock at the end of loop

    timeDifference = (double)(end - begin) ;
    printf("%lf\n",timeDifference / CLOCKS_PER_SEC) ;

    return EXIT_SUCCESS;
}

/*******************BUFFERED IO************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

int main()
{
    /*****************Declaration of local variables***************/
    int blocksize , blockcount ;
    FILE * fd;
    size_t fileWrite;

    /********Creation of file and checking its error condition*********/
    fd = fopen("rawio","w");   //Permission : write and if file exist it is truncated to zero
    if ( !fd ) {
        perror("ERROR!!!!\n");
    }

    /**********Taking inputs from the user*********/
    printf("Enter no of times buffer to be written : \n");
    scanf("%d" , &blockcount);
    printf("Enter size of the buffer : \n");
    scanf("%d" , &blocksize);

    char buf[blocksize];

    /*****File Writing and Duration Measurement****/
    clock_t begin = clock(); // Initialising the clock at the beginning of the loop
    while ( blockcount ) {
        fileWrite = fwrite(buf , blocksize , 1 , fd);   //writing form buf of size blocksize to fd blockcount no of times
        blockcount--;
    }
    if(-1 == fileWrite) {
        perror("ERROR!!!!!\n");
    }

    clock_t end = clock(); // Storing the clock value at the end of the loop
    double timediff = (double)(end - begin);
    printf("Running Time : %lf\n", timediff / CLOCKS_PER_SEC);

    return EXIT_SUCCESS;
}
