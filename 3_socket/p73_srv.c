#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void error_handling(char * message);

int main (int argc, char * argv[]) 
{
	int serv_sock, conn_sock;

	struct sockaddr_in serv_addr, clnt_addr;

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);	
			
	if(argc != 2){
		printf("Usage : %s <port> \n", argv[0]);
		exit(1);
	}


	if(serv_sock == -1) 
			error_handling("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
		error_handling("bind() error");

	if (listen(serv_sock, 5) == -1)
		error_handling("listen() error");

	int clnt_addrsz = sizeof(clnt_addr);
	char message[BUF_SIZE];
	int str_len;
	int i;

	for(i=0; i < 5; i++) {
	
	conn_sock = accept(serv_sock, (struct sockaddr*) &clnt_addr, &clnt_addrsz);			 	
	if(conn_sock == -1)
			error_handling("accpet() error");
	else 
			printf("Connected client %d \n", i+1);
	
	while((str_len=read(conn_sock, message, BUF_SIZE))!=0) 
		write(conn_sock, message, str_len);
	
	close(conn_sock);
	}
	close(serv_sock);
	return 0;
}


void error_handling(char * message){
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

