/* Multicast Sender */
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int sck;
	struct sockaddr_in grpSck;
	struct in_addr lclInterface;
	char buf[1024];
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

	bzero((char *) &grpSck, sizeof(grpSck));
	grpSck.sin_family = AF_INET;
	grpSck.sin_addr.s_addr = inet_addr("226.1.2.3");
	grpSck.sin_port = htons(5435); 

	lclInterface.s_addr =htonl(INADDR_ANY);

	if(setsockopt(sck, IPPROTO_IP, IP_MULTICAST_IF, (char *)&lclInterface, sizeof(lclInterface)) < 0)
	{
  		printf("Local interface error\n");
  		exit(1);
	}
	else
	{
		printf("Local interface set\n");
	}

	while(1)
	{
		blen=sizeof(buf);
		bzero(buf,blen);
	
		printf("\nEnter multicast message :");
		fgets(buf,blen,stdin);

		if(sendto(sck,buf,blen,0, (struct sockaddr*)&grpSck, sizeof(grpSck)) < 0)
		{
			printf("Error in sending message");
		}
		else
		{
	  		printf("Message sent successfully\n"); 
		}
	}	
	return 0;	
}
