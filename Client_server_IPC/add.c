#include"headers.h"
#include"proto.h"
void wait_funct(void);
void signal_funct(void);
int kkey;


int main()
{
	printf("%s: Started\n",__FILE__);
	int fd,rret,fret,wfd,wret;
	kkey=semget(601,1,0666|IPC_CREAT);
	if(kkey==-1){
		perror("semget");
		exit(1);
	}
//	printf("after semget\n");
	real_sv.val=1;
	semctl(kkey,0,SETVAL,real_sv);
	struct result ans;
	struct request c_data;
//	printf("before wait\n");
//	printf("after wait\n");
	fd=open(SNDFIFO,O_RDONLY);
	if(fd==-1) {
		perror("open");
		exit(1);
	}
	wait_funct();
//	printf("%s: after open\n",__FILE__);
	rret=read(fd,&c_data,sizeof(struct request));
	if(rret==-1) {
		perror("read");
		exit(1);
	}
//	printf("%s: read %d bytes\n",__FILE__,rret);

	printf("%s: oprn1 = %d\n",__FILE__,c_data.data.oprn1);
	printf("%s: oprn2 = %d\n",__FILE__,c_data.data.oprn2);
	printf("%s: opr = %c\n",__FILE__,c_data.data.opr);
	printf("%s: pid = %d\n",__FILE__,c_data.data.pid);

	ans.type=c_data.data.pid;
	ans.res= c_data.data.oprn1 + c_data.data.oprn2;
//	ans.a_pid=getpid();
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
	count=1;
	signal_funct();
	//sem_post(&sem);
	exit(0) ;

}
void wait_funct(void)
{
        sem_operation.sem_num=0;
        sem_operation.sem_op=-1;
        sem_operation.sem_flg=SEM_UNDO;
        if(semop(kkey,&sem_operation,1)==-1) {
                perror("semop");
                exit(1);
        }
}
void signal_funct(void)
{
        sem_operation.sem_num=0;
        sem_operation.sem_op=1;
        sem_operation.sem_flg=SEM_UNDO;
        if(semop(kkey,&sem_operation,1)==-1) {
                perror("semop");
                exit(1);
        }
}

