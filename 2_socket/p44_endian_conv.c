#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	unsigned short host_port = 0x1234;
	unsigned short net_port;	
	unsigned long host_addr = 0x12345678;
	unsigned long net_addr;

	net_port = htons(host_port);
	net_addr = htonl(host_addr);

	printf("net_port :%x, host_port : 0x1234\n", net_port);
	printf("net_addr :%lx  host_addr : 0x12345678\n", net_addr);

	return 0;

}

