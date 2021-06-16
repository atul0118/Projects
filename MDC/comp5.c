#include"headers.h"
#include"prototypes.h"

int comp5(int fd)
{
	unsigned char byt;
	char ch;
	int fd1,size
	size=lseek(fd,0,2);
	lseek(fd,0,0);
	char *file=(char*)malloc(20);
	printf("%s started\n",__func__);
	printf("Enter the name for compressed file\n");
	scanf(" %s",file);
	fd1=openfile(file,"WR_ONLY");
	while(1)
	{
		byt=byt^byt;
		rb=read(fd,&ch,1);
	}
}
