#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
int main()
{
    int fd;
    char *c="Hello World\n";
    fd=open("hello.txt",O_CREAT|O_WRONLY|O_TRUNC,S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IROTH);
    if(fd==-1)
        perror("ERROR!!!\n");
    ssize_t nr=write(fd,c,strlen(c));
    if(nr==-1)
        perror("ERROR!!!\n");
    return 0;
}
