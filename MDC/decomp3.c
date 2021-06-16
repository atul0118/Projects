#include"headers.h"
#include"prototypes.h"

int decomp3(char* ma)
{
	char byt;
	printf("%s started\n", __func__);
	char* file=(char*)malloc(20);
	char* ufile=(char*)malloc(20);
	printf("Enter the name of compressed file: ");
	scanf(" %s",file);
	char ch,cp_ch,c_w,b1;
	int cfd,ufd,r,i;
	cfd=openfile(file);
	printf("Enter the name of file to save unencrypted data: ");
	scanf(" %s",ufile);
	ufd=openfile(ufile);
	int k=1;

	while(k==1)
	{
		byt ^= byt;
		r=read(cfd,&ch,1);
		if(r==0){ break; }
		cp_ch=ch;
		ch>>5;
		i=(int)ch;
		c_w=*(ma+i);
		write(ufd,&c_w,1);
		
		i=0;
		ch=cp_ch;
		ch<<3;
		ch>>5;
		i=(int)ch;
		c_w=*(ma+i);
		write(ufd,&c_w,1);

		b1 ^= b1;
		ch=cp_ch;
		ch<<6;
		ch>>5;
		b1=ch;

		r=read(cfd,&ch,1);
		cp_ch=ch;
		ch>>7;
		b1= b1|ch;
		i=(int)b1;
		c_w=*(ma+i);
		write(ufd,&c_w,1);
		k--;




	}
}
