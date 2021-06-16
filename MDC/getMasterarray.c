#include"headers.h"
#include"prototypes.h"

char* getMasterarray(char* key)
{
	int decfd,size;
	char* ma;
	decfd=openfile(key);
        if(decfd==-1) { perror("open"); exit(EXIT_FAILURE); }
        size=lseek(decfd,-1,SEEK_END);
        lseek(decfd,0,SEEK_SET);
        ma=(char*)malloc(size);
        int r=read(decfd,ma,size);
        if(r==-1) { perror("read"); exit(EXIT_FAILURE);}
        close(decfd);
        //printf("%s",ma);
        printf("Key obtained for encryption file is: %s\n",ma);
        //printf("Size of key: %d\n",strlen(ma));
	return ma;

}
