#include"headers.h"
#include"proto.h"
void* routine_1(void*);
void* routine_2(void*);
int flag;

int main()
{
	int tid,ret;
	ret=pthread_create(&tid,NULL,routine_1,(void*)NULL);
	if(ret==-1) {
		perror("pthread_create");
		exit(1);
	}
	while(1);

}

void* routine_1(void* arg)
{
	int socket_fd,bind_ret,listen_id,dup_fd;
        int client_length;
        char ch;
	    int ret,tid;
        struct sockaddr_un client_addr;
        struct sockaddr_un server_addr;
        client_length=sizeof(struct sockaddr_un);
        server_addr.sun_family=AF_INET;
        strcpy(server_addr.sun_path,"server_socket");

        /******** creating socket *********/
        socket_fd=socket(AF_UNIX,SOCK_STREAM,0);
        if(socket_fd == -1) {
                perror("socket");
                exit(1);
        }

        /********* Binding socket (name is in server_addr,defined by me.) ************/
        bind_ret=bind(socket_fd,(struct sockaddr*)&server_addr,sizeof(struct sockaddr_un));
        if(bind_ret == -1) {
                perror("bind");
                exit(1);
        }
	flag=1;
	while(1) {
		printf("Waiting for client\n");

		/********** Making socket passive using listen() ********************/
                listen_id=listen(socket_fd,2);
                if(listen_id == -1) {
                        perror("listen");
                        exit(1);
                }

		if(flag) {
			ret=pthread_create(&tid,NULL,routine_2,(void*)socket_fd);
			if(ret==-1) {
				perror("pthrea_create");
				exit(1);
			}
		}
		sleep(2);
		flag=0;
	}
}

void* routine_2(void* arg)
{
	int *i;
	i=(int*)arg;
	struct request req;
	struct sockaddr_un client_addr;
	int client_length = sizeof(struct sockaddr_un);
	int dup_fd;
	 dup_fd=accept(i,(struct sockaddr*)&client_addr,&client_length);
         if(dup_fd == -1) {
                perror("accept");
                exit(1);
	 }
 	read(dup_fd,&req,sizeof(struct request));
	printf("%s: oprn1 = %d\n",__FILE__,req.data.oprn1);
	printf("%s: oprn2 = %d\n",__FILE__,req.data.oprn2);
	printf("%s: opr = %c\n",__FILE__,req.data.opr);
	printf("%s: pid = %d\n",__FILE__,(int)req.data.pid);
	int size=sizeof(struct request);
	int wret= write(dup_fd,&size,4);
	if(wret == -1)
	{
		perror("wret");
		exit(1);
	}
	flag=1;



}
