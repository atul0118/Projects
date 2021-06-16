#include"headers.h"
#include"prototypes.h"

int decomp4(char* ma)
{
	char* file=(char*)malloc(20);
	char* ufile=(char*)malloc(20);
	printf("Enter the name of compressed file: ");
	scanf(" %s",file);
	char c,ch,ca;
	int cfd,i,l,r,ufd;
	l=strlen(ma);
	cfd=openfile(file);
	printf("Enter the name of file to save unencrypted data: ");
	scanf(" %s",ufile);
	ufd=openfile(ufile);
	

	while(1)
	{
		ca = ca^ca;
		r=read(cfd,&c,1);
		if(r==0) { break;}
		ca=c;
		ca=ca>>4;
		i=(int)ca;
		ch=*(ma+i);
		write(ufd,&ch,1);

		//r=read(cfd,&c,1);
		//if(r==0) { break;}
		ca=c;
		ca=ca<<4;
		ca=ca>>4;
		i=(int)ca;
		ch=*(ma+i);
		write(ufd,&ch,1);

	}
	printf("DECOMPRESSION SUCCESSFUL!! \n");
	
}
