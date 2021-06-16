#include"headers.h"
#include"prototypes.h"
int comp3(char* ma,int fd)
{
	char byt,c,cp_c;
	int r,cfd,i,size;
	char ch;
	char *file;
	file=(char*)malloc(20);
	printf("%s started\n", __func__);
	printf("Enter the name for compressed file: ");
	scanf(" %s",file);
	printf("\n");
	cfd=open(file,O_WRONLY|O_CREAT);
	size=lseek(fd,0,2);
	lseek(fd,0,0);
	while(1)
	{
		byt ^= byt;      								// 00000000
		r=read(fd,&ch,1);								// character 1
		if(r==-1) { perror("read"); exit(EXIT_FAILURE);}
		if(--size == 0) { printf("EOF FOUND\n"); break;}
		i=find_index(ma,ch);
		sprintf(&c,"%d",(char)i);
		c<<5;
		byt |= c;
		
		r=read(fd,&ch,1);								// character 2
		if(r==-1) { perror("read"); exit(EXIT_FAILURE);}
		if(--size == 0) { printf("EOF FOUND\n"); break;}
		i=find_index(ma,ch);
		sprintf(&c,"%d",(char)i);
		c<<5;
		c>>3;
		byt |= c;

		r=read(fd,&ch,1);								// character 3
		if(r==-1) { perror("read"); exit(EXIT_FAILURE);}
		if(--size == 0) { printf("EOF FOUND\n"); break;}
		i=find_index(ma,ch);
		sprintf(&c,"%d",(char)i);
		c<<5;
		cp_c=c;
		c>>6;
		byt |= c;
		write(cfd,&byt,1);								// Byte completed

		byt ^= byt;       								//00000000 
		cp_c << 2;
		byt|=cp_c;
		r=read(fd,&ch,1);								// character 4
		if(r==-1) { perror("read"); exit(EXIT_FAILURE);}
		if(--size == 0) { printf("EOF FOUND\n"); break;}
		i=find_index(ma,ch);
		sprintf(&c,"%d",(char)i);
		c<<5;
		c>>1;
		byt |=c;


		r=read(fd,&ch,1);								// character 5
		if(r==-1) { perror("read"); exit(EXIT_FAILURE);}
		if(--size == 0) { byt |= 0b00001111; write(cfd,&byt,1); printf("EOF FOUND\n"); break;}
		i=find_index(ma,ch);
		sprintf(&c,"%d",(char)i);
		c<<5;
		c>>4;
		byt |=c;


		r=read(fd,&ch,1);								// character 6
		if(r==-1) { perror("read"); exit(EXIT_FAILURE);}
		if(--size == 0) { printf("EOF FOUND\n"); break;}
		i=find_index(ma,ch);
		sprintf(&c,"%d",(char)i);
		c<<5;
		cp_c=c;
		c>>7;
		byt |=c;
		write(cfd,&byt,1);								//Byte completed

		byt ^= byt;									//00000000
		cp_c<<1;
		byt |= cp_c;
		r=read(fd,&ch,1);								// character 7
		if(r==-1) { perror("read"); exit(EXIT_FAILURE);}
		if(--size == 0) { printf("EOF FOUND\n"); break;}
		i=find_index(ma,ch);
		sprintf(&c,"%d",(char)i);
		c<<5;
		c>>2;
		byt |= c;


		r=read(fd,&ch,1);								// character 8
		if(r==-1) { perror("read"); exit(EXIT_FAILURE);}
		if(--size == 0) { printf("EOF FOUND\n"); break;}
		i=find_index(ma,ch);
		sprintf(&c,"%d",(char)i);
		c<<5;
		c>>5;
		byt |= c;									//Byte completed
		write(cfd,&byt,1);

		
	}
		
	

	printf("%s ended\n", __func__);
}
