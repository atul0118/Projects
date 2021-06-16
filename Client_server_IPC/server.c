#include"headers.h"
#include"proto.h"
#include<pthread.h>

int main()
{
	int i,tret,r1,r2,se_ret,fret,fret2;
	long int tid;
	i=0;
//	int count=0;
	flag=1;
	pthread_attr_t attribute;
	r2=pthread_attr_init(&attribute);
	if(r2 != 0) {
		perror("pthread_attr_init");
		exit(1);
	}
	r1=pthread_attr_setdetachstate(&attribute,PTHREAD_CREATE_DETACHED);
	if(r1 != 0) {
		perror("pthread_attr_setdetachstate");
		exit(1);
	}	


	/***** creating fifo for sending data to opeartor ********/
	if(access(SNDFIFO,F_OK)==-1) {
		fret=mkfifo(SNDFIFO,0666);
		if(fret==-1) {
			perror("mkfifo");
			exit(1);
		}
	}

	/*************** creating fifo for result ********/
	if(access(RECFIFO,F_OK)==-1) {
		fret2=mkfifo(RECFIFO,0666);
		if(fret2==-1) {
			perror("mkfifo");
			exit(1);
		}
	}
			

	/************** main thread creating infinite threads **************/
	while(1) {
		if(flag) {
			i++;
			tret=pthread_create(&tid,&attribute,routine,(void*)i);
			if(tret!=0) {
				perror("pthread_create");
				exit(1);
			}
		//	printf("%s: thread %d created successfully\n",__FILE__,i);
			flag=0;						// resetting the flag //
			printf("^^^^^^^^^^^^^^^^^^^^^^ number of thread  %d ^^^^^^^^^^^^^^^^^^^^^^^^^^^\n",i);
		}
	}
	
}
void* routine(void* arg)
{

	int msgid,msgid2,rret,sret,fork_ret,fd,wret,rret2,rfd,se_ret;
	struct request c_data;
	struct result ans;
	int* i;
	i=(int*)arg;
	int c;
	c=(int)i;
	if((access("result",F_OK)==-1)) {
			int z=mkfifo("result",0666);
			if(z==-1) {
				perror("mkfifo");
				exit(1);
			}
				}
	/********* creating thread semaphore **********/
	se_ret=sem_init(&sem,1,1);
	if(se_ret != 0) {
		perror("sem_init");
		exit(1);
	}

	/********** creating message queue *********/
	msgid=msgget(500,0666|IPC_CREAT);
	if(msgid==-1) {
		perror("msgget");
		exit(1);
	}
	//printf("%s: %d--after creating request MQ\n",__FILE__,i);
	
	/*********** creating result message queue *******/
	msgid2=msgget(501,0666|IPC_CREAT);
	if(msgid2==-1) {
		perror("msgget");
		exit(1);
	}
//	printf("%s: %d--after creating result MQ\n",__FILE__,i);

	/****** reading from queue *****************/
	rret=msgrcv(msgid,(void*)&c_data,sizeof(struct request),c_data.data.pid,0);
	if(rret==-1) {
		perror("msgrcv");
		exit(1);
	}
//	printf("%s: %d--after reading from request MQ\n",__FILE__,i);
/*	printf("%s: oprn1= %d\n",__FILE__,c_data.data.oprn1);
	printf("%s: oprn2= %d\n",__FILE__,c_data.data.oprn2);
	printf("%s: opr= %c\n",__FILE__,c_data.data.opr);
	printf("%s: client pid= %d\n",__FILE__,c_data.data.pid);*/



	signal(SIGCHLD,SIG_IGN);
	fork_ret=fork();
	switch(fork_ret) {
		case -1:
			perror("fork");
			exit(1);
		case 0:
			//printf("%s: I am child process :)\n",__FILE__);
			switch(c_data.data.opr) {
				case '+':
					execl("./add","add",NULL);
				case '-':
					execl("./sub","sub",NULL);
				default:
					printf("hi\n");
			}

		default:
			printf("%s: I am parent process of the new thread\n",__FILE__);
	}
//	printf("%s: %d--after sem_wait\n",__FILE__,i);
	sem_wait(&sem);						/// semaphore wait ///
	fd=open(SNDFIFO,O_WRONLY);
	if(fd==-1) {
		perror("open");
		printf("error of %d\n",i);
		exit(1);
	}
//	printf("%s: after open\n",__FILE__);
	/***** writing client request into fifo *******/
	wret=write(fd,&c_data,sizeof(struct request));
	if(wret==-1) {
		printf("write");
		printf("error of %d\n",i);
		exit(1);
	}
//	printf("%s: %d--after writing to request fifo\n",__FILE__,i);
//	printf("%s: wrote %d bytes\n",__FILE__,wret);
	close(fd);
	rfd=open(RECFIFO,O_RDONLY);
	if(rfd==-1) {
		perror("open");
		printf("error of %d\n",i);
		exit(1);
	}
	int ec;
//	wait(&ec);

	/************** reading result from fifo *******/
	rret2=read(rfd,&ans,sizeof(struct result));
	if(rret2==-1) {
		perror("read");
		printf("error of %d\n",i);
		exit(1);
	}
//	printf("%s: %d--after reading result from result fifo\n",__FILE__,i);
/*	printf("%s: Read %d bytes\n",__FILE__,rret2);*/
	printf("%s: result= %d and PID = %d\n",__FILE__,ans.res,ans.type);
	close(rfd);

	/*int rz=open("result",O_WRONLY);
	if(rz==-1) {
		perror("open");
		exit(1);
	}
	write(rz,&ans,sizeof(struct result));*/
//	count=0;	
	/***************** writing result to msgqueue *************/
	sret=msgsnd(msgid2,&ans,sizeof(struct result),0);
	if(sret==-1) {
		perror("msgsnd");
		printf("error of %d\n",i);
		exit(1);
	}
	sem_post(&sem);
//	printf("%s: %d--after writing result to MQ\n",__FILE__,i);
//	kill(ans.a_pid,SIGKILL);
//	printf("%s: data written into message queue\n",__FILE__);
//	printf("%s: %d--after sem_post\n",__FILE__,i);
	//system("unlink result");
	printf("%s: *************** thread %d ends ********************\n",__FILE__,i);
	sem_post(&sem);
	flag=1; 				// setting flag for server //


}
