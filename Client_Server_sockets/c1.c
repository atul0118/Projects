#include"headers.h"
#include"proto.h"


int main()
{
	int socket_fd,bind_ret,listen_ret,cret;
	struct request req;
	req.data.oprn1=10;
	req.data.oprn2=0;
	req.data.opr='+';
	req.data.pid=getpid();

        int client_length;
        char ch;
        char buff[4];
        struct sockaddr_un client_addr;
        struct sockaddr_un server_addr;
        client_length=sizeof(struct sockaddr_un);
        server_addr.sun_family=AF_UNIX;
        strcpy(server_addr.sun_path,"server_socket");

        /******** creating socket *********/
        socket_fd=socket(AF_UNIX,SOCK_STREAM,0);
        if(socket_fd == -1) {
                perror("socket");
                exit(1);
        }



                /************** Connecting to server **********************/
                cret=connect(socket_fd,(struct sockaddr*)&server_addr,sizeof(struct sockaddr_un));
                if(cret == -1) {
                        perror("connect");
                        exit(1);
                }
		write(socket_fd,&req,sizeof(struct request));
		printf("request sent sucessfully :)\n");
		printf("reading request\n");
		sleep(1);
		int size;
		read(socket_fd,&size,4);
		printf("I got %d from server!!!!!\n",size);

}


