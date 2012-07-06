/* Multicast Receiver */
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int sck;
	struct sockaddr_in lclSck;
	struct ip_mreq grp;
	struct in_addr lclInterface;
	char buf[1024];
	int reuse = 1;
	int blen;

	sck=socket(AF_INET,SOCK_DGRAM,0);

	if(sck<0)
	{
		printf("Socket creation error\n");
		exit(1);
	}
	else
	{
		printf("Socket created successfully\n");
	}	
	
	if(setsockopt(sck, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) < 0)
	{
		perror("Socket reuse address error\n");
		close(sck);
		exit(1);
	}
	else
	{
		printf("Socket reuse address successfull\n");
	}		

	bzero((char *)&lclSck, sizeof(lclSck));
	lclSck.sin_family = AF_INET;
	lclSck.sin_port = htons(5435);
	lclSck.sin_addr.s_addr = INADDR_ANY;

	if(bind(sck, (struct sockaddr*)&lclSck, sizeof(lclSck)))
	{
		perror("Error in binding socket\n");
		close(sck);
		exit(1);
	}
	else
	{
		printf("Socket binding successfull\n");
	}
 
	grp.imr_multiaddr.s_addr = inet_addr("226.1.2.3");
	grp.imr_interface.s_addr = htonl(INADDR_ANY);

	if(setsockopt(sck, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&grp, sizeof(grp)) < 0)
	{
		printf("Error in joining group\n");
		close(sck);
		exit(1);
	}
	else
	{
		printf("Group joined successfully\n");
 	}
	while(1)
	{
		blen=sizeof(buf);
		bzero(buf,blen);
		if(read(sck,buf,blen) < 0)
		{
			printf("Message read error\n");
			close(sck);
			exit(1);
		}
		else
		{
			printf("\nMessage from multicast sender is: %s",buf);
		}

	}
	return 0;
}
