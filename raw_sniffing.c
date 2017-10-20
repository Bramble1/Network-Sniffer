#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*Raw sniffing, purpose for unswitched networks (Ethernet packets), 
 * where packets travel to
 * every host in the network until it reaches its destination. AS well as this
 * make sure device is in promiscuous mode, which causes all packets to be
 * looked at.*/

#define LIMIT 50
void hex_dump(const unsigned char *buffer, const unsigned int len);

int main (int args, char *argv[])
{
	int packet_len , _socket;
	int s_created = 0;
	u_char buf[9000];

	/*insufficient arguments*/
	if(args != 2)
	{
		printf("<Arguments>\n");
		exit(1);
	}

	/*checking what type of packets that want to be sniffed*/
	if(strcmp(argv[1],"-tcp")==0)
	{
		if((_socket = socket(AF_INET,SOCK_RAW,IPPROTO_TCP)) ==-1)
			perror("in socket");
		s_created = 1;
	}
	else if(strcmp(argv[1],"-udp")==0)
	{
		if((_socket = socket(AF_INET,SOCK_RAW,IPPROTO_UDP)) ==-1)
			perror("in socket");
		s_created = 1;
	}
	else if(strcmp(argv[1],"-icmp")==0)
	{
		if((_socket = socket(AF_INET,SOCK_RAW,IPPROTO_ICMP))==-1)
			perror("in socket");
		s_created = 1;
	}
	else if(strcmp(argv[1],"-raw")==0)
	{
		if((_socket = socket(AF_INET,SOCK_RAW,IPPROTO_RAW))==-1)
			perror("in socket");
		s_created = 1;
	}

	/*begin listening*/
	if(s_created == 1){
	for(int i=0; i<LIMIT;i++)
	{
		packet_len = recv(_socket,buf,8000,0);
		printf("%d byte sized packet recieved.\n",packet_len);
		hex_dump(buf,packet_len);
	}
	}
}

/*function used to dump and output the packets recieved in a hexadecimal format.*/
void hex_dump(const unsigned char *buffer , const unsigned int len)
{
	unsigned char byte;
	unsigned int i,j;

	for(int i=0; i<len; i++)
	{
		byte = buffer[i];
		printf("%02x " , buffer[i]);

		if(((i%16)==15) || (i==len-1))
		{
			for(j=0; j<15-(i%16);j++)
				printf(" ");
			printf("| ");

			for(j=(i-(i%16)); j<=i; j++)
			{
				byte = buffer[j];
				if((byte>32) && (byte <127))
					printf("%c",byte);
				else
					printf(".");
			}
			putchar('\n');
		}
	}
}
