#include"headers.h"

int main()
{
	int msgid1=msgget(500,0666|IPC_CREAT);
	if(msgid1==-1) {
		perror("msgget");
		exit(1);
	}


	int msgid2=msgget(501,0666|IPC_CREAT);
	if(msgid2==-1) {
		perror("msgget");
		exit(1);
	}

	msgctl(msgid1,IPC_RMID,0);
	msgctl(msgid2,IPC_RMID,0);

}

