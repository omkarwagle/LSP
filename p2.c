#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include<stdio.h>
main()
{
	char fdw,fdr;
	int i;
	char *buf="HELLO ELEAR!!!!\n";
	int len=strlen(buf);
	fdw=open("foo.txt",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP|S_IROTH);
	if(fdw==-1)
		perror("ERROR\n");
	ssize_t nw=write(fdw,buf,len);
	if(nw==-1)
		perror("ERROR\n");
	fdr=open("bar.txt",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP|S_IROTH);
	if(fdr==-1)
		perror("ERROR\n");
	ssize_t nr;
	while(len!=0 && (nr=write(fdr,buf,len))>0)
	{
		if(nr==-1)
			perror("ERROR\n");
		buf+=nr;
		len-=nr;
	}

}
