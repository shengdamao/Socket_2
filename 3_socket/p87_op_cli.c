#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define RLT_SIZE 4
#define OPSZ 4

void error_handling(char *message);

int main(int argc, char * argv[]) 
{
	int sock;
	
	char opmsg[BUF_SIZE];
//	char message[BUF_SIZE];
	
	if(argc!=3) {
		printf("Usage : %s <IP> <port>", argv[0]);
		exit(1);
	}

	struct sockaddr_in serv_addr;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
			error_handling("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));
	
	if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))==-1)
			error_handling("connect() error");
	else
			printf("connected...");

//	int str_len, recv_len, recv_cnt;
	int opnd_cnt, i;
	
	fputs("Operand count:", stdout);
	scanf("%d", &opnd_cnt);
	opmsg[0] = opnd_cnt;

	for(i=0; i<opnd_cnt; i++)
	{
		printf("Operand %d: \n", i+1);
		scanf("%d", (int*)&opmsg[i*OPSZ + 1]);
	}
	
	fgetc(stdin);
	fputs("operator: ", stdout);
	scanf("%c", &opmsg[opnd_cnt*OPSZ + 1]);
	write(sock, opmsg, opnd_cnt*OPSZ+2);

	int result;
	read(sock, &result, RLT_SIZE);

	printf("Operation Result: %d \n", result);
	close(sock);
	return 0;
}

void error_handling(char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

