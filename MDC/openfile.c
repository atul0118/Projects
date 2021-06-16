#include"headers.h"
#include"prototypes.h"
int openfile(char*file)
{
	int fd;
	fd=open(file,O_RDWR|O_CREAT);
	if(fd==-1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	return fd;

}
