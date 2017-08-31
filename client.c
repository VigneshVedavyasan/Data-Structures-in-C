#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char *argv[])
{
	int sockfd;
	struct sockaddr_in server;
	char message[1000],server_reply[2000];
	sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
	if(sockfd<0)
	{
		perror("Cannot create socket!\n");
		return EXIT_FAILURE;
	}
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(9999);
	if(connect(sockfd,(struct sockaddr*)&server,sizeof(server))<0)
	{
		perror("Couldn't establish connection!\n");
		return EXIT_FAILURE;
	}
	while(1)
	{
		printf("Enter message : ");
		scanf("%s",message);
		
		if(send(sockfd,message,strlen(message),0)<0)
		{
			perror("Send failed!\n");
			return EXIT_FAILURE;
		}
		if(recv(sockfd,server_reply,2000,0)<0)
		{
			perror("recv failed!\n");
			break;
		}
		printf("Server reply : ");
		puts(server_reply);
		memset(server_reply,'\0',2000);
	}
	close(sockfd);
	return EXIT_SUCCESS;
}