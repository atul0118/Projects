#include"headers.h"
#include"proto.h"

int main()
{
	printf("%s: Started\n",__FILE__);
	int fd,rret,fret,wfd,wret;
	struct result ans;
	struct request c_data;
	fd=open(SNDFIFO,O_RDONLY);
	if(fd==-1) {
		perror("open");
		exit(1);
	}
//	printf("%s: after open\n",__FILE__);
	rret=read(fd,&c_data,sizeof(struct request));
	if(rret==-1) {
		perror("read");
		exit(1);
	}
/*	printf("%s: read %d bytes\n",__FILE__,rret);

	printf("%s: oprn1 = %d\n",__FILE__,c_data.data.oprn1);
	printf("%s: oprn2 = %d\n",__FILE__,c_data.data.oprn2);
	printf("%s: opr = %c\n",__FILE__,c_data.data.opr);
	printf("%s: pid = %d\n",__FILE__,c_data.data.pid); */

	ans.type=c_data.data.pid;
	ans.res= c_data.data.oprn1 - c_data.data.oprn2;

	/*********** creating resulting fifo **************/
	if(access(RECFIFO,F_OK)==-1) {
		fret=mkfifo(RECFIFO,0666);
		if(fret==-1) {
			perror("mkfifo");
			exit(1);
		}
	}

	/************* writing result into fifo ************/
	wfd=open(RECFIFO,O_WRONLY);
	if(wfd==-1) {
		perror("open");
		exit(1);
	}

	wret=write(wfd,&ans,sizeof(struct result));
	if(wret==-1) {
		perror("write");
		exit(1);
	}
//	printf("%s: Wrote %d bytes\n",__FILE__,wret);


}
