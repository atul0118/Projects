#include"headers.h"
#include"proto.h"
void wait_func(void);
void signal_func(void);

int main()
{
	struct request c_data;
	struct result ans;
	int msgid1,msgid2,sret,rret;

	/*********** creating semaphore ***********/
	kernel_key=semget(600,2,0666|IPC_CREAT);

	/************* initialize semaphore *******/
	real_sv.val=1;
	semctl(kernel_key,0,SETVAL,real_sv);

	/******* create request message queue ******/
	msgid1=msgget(500,0666|IPC_CREAT);
	if(msgid1==-1) {
		perror("msgget");
		exit(1);
	}

	/********** create result message queue *****/
	msgid2=msgget(501,0666|IPC_CREAT);
	if(msgid2==-1) {
		perror("msgget");
		exit(1);
	}
	
	/******* initializing client data ***********/
	c_data.data.oprn1=40;
	c_data.data.oprn2=0;
	c_data.data.opr='+';
	c_data.data.pid=getpid();
	c_data.type=1;

	/************* wait semaphore ****************/
	wait_func();
	/******** sending data into message queue ****/
	sret=msgsnd(msgid1,(void*)&c_data,sizeof(struct request),0);
	if(sret==-1) {
		perror("msgsnd");
		exit(1);
	}

//	printf("%s: Data written into mq\n",__FILE__);
	signal_func();
//	printf("%s: ends\n",__FILE__);
	
	/************** reading result from msg queue ***********/
	rret=msgrcv(msgid2,(void*)&ans,sizeof(struct result),getpid(),0);
	if(rret==-1) {
		perror("msgrcv");
		exit(1);
	}
	printf("%s: Result is %d\n",__FILE__,ans.res);
	printf("******************************************\n");


}
void wait_func(void)
{
	sem_operation.sem_num=0;
	sem_operation.sem_op=-1;
	sem_operation.sem_flg=SEM_UNDO;
	if(semop(kernel_key,&sem_operation,1)==-1) {
		perror("semop");
		exit(1);
	}
}
void signal_func(void)
{
	sem_operation.sem_num=0;
	sem_operation.sem_op=1;
	sem_operation.sem_flg=SEM_UNDO;
	if(semop(kernel_key,&sem_operation,1)==-1) {
		perror("semop");
		exit(1);
	}
}
