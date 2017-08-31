#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<pthread.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main(int argc,char *argv[])
{
  int c,clientfd,sockfd,read_size;
  struct sockaddr_in server,client;
  char client_message[2000];
  sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
  if(sockfd<0)
  {
    perror("Error in socket creation!");
    return EXIT_FAILURE;
  }
  puts("Socket Connected!\n");
  
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_family = AF_INET;
  server.sin_port = htons(9999);
  if(bind(sockfd,(struct sockaddr*)&server,sizeof(server))<0)
  {
    perror("Bind failed!\n");
    return EXIT_FAILURE;
  }
  puts("Bind done!\n");
  
  listen(sockfd,3);
  puts("Listening to incoming connection...\n");
  
  c = sizeof(struct sockaddr_in);
  clientfd = accept(sockfd,(struct sockaddr*)&client,(socklen_t*)&c);
  if(clientfd<0)
  {
    perror("Accept failed!\n");
    return EXIT_FAILURE;
  }
  puts("Connection Accepted!\n");
  
  while((read_size = recv(clientfd,client_message,2000,0))>0)
  {
    write(clientfd,client_message,strlen(client_message));
    memset(client_message,'\0',2000);
  }
  if(read_size==0)
  {
    perror("No input received from client!\n");
    fflush(stdout);
  }
  else if(read_size<0)
  {
    perror("recv failed!\n");
    return EXIT_FAILURE;
  }
  close(sockfd);
  return EXIT_SUCCESS;
}