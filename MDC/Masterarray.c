#include"headers.h"
#include"prototypes.h"
char* Masterarray(int fd)
{
	int i,ret,encfd;
	unsigned char size;
	int t;
	char ch;
	int ret2;
	char* ma;
	char* sma=(char*)malloc(20);
	ma=NULL;
	size=lseek(fd,0,SEEK_END)-1;
	//ma=(char*)malloc(size*sizeof(char));
	lseek(fd,0,SEEK_SET);

	i=0;
	while(size)
	{
		ret=read(fd,&ch,1);
		if(ret== -1)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}
		t=unique(ch,i,ma);
		//printf("%c",ch);
		//printf("%d",t);
		if(t==1)
		{
			ma=realloc(ma,i+1);
			*(ma+i)=ch;
			//printf("%c",*(ma+i));
			i++;
		}
		size--;
		
	}
//	ma=realloc(ma,i+1);
//	*(ma+i+1)='\0';
/*	for(int k=0;k<strlen(ma);k++)
	{
		printf("ma(%d)=%c\n",k,*(ma+k));
	}*/
	//printf("%s\n",ma);
	printf("Enter the file name to save encryption key: ");
	scanf(" %s",sma);
	encfd=openfile(sma);
	if(encfd==-1) { perror("open"); exit(EXIT_FAILURE);}
	write(encfd,ma,strlen(ma));
	close(encfd);
	return ma;

}

