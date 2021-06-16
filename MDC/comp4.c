#include"headers.h"
#include"prototypes.h"

int comp4(char* ma,int fd)
{
	unsigned char byt,c;
	int size,i,rb,fd1;
	char ch;
	char* file;
	size=lseek(fd,0,SEEK_END);
	lseek(fd,0,SEEK_SET);
	file=(char*)malloc(20);
	printf("Enter the name for compressed file: ");
	scanf(" %s",file);
	fd1=openfile(file);
	while(1)
	{
		byt=byt^byt;
		rb=read(fd,&ch,1);
		if(rb==0)
		{
			//byt1 = byt1|0xF0;
			//write(fd1,&byt1,1);
			break;
		}
		i=find_index(ma,ch);
		c=(char)i;
		c=c<<4;
		byt=byt|c;
		rb=read(fd,&ch,1);
		if(rb==0)
		{
			//byt1=byt1|0x0F;
			//write(fd1,&byt1,1);
			break;
		}
		i=find_index(ma,ch);
		c=(char)i;
		c=c<<4;
		c=c>>4;
		byt=byt|c;
		write(fd1,&byt,1);


	}


}
