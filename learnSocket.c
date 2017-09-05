
/* Version 0.1
 * Presently only one client is handled at a time by the threads 
 * In the present functionality anything sent by a client is echoed by server to ease debugging
 * Asynchronous chat feature will be incorporated in the future versions.
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<pthread.h>
#include<arpa/inet.h>
#include<netinet/in.h>

void *connection_handler(void *socket_desc)
{
  int sock = *(int*)socket_desc;
  int read_size;
  char *message,client_message[2000];
  
  while((read_size=recv(sock,client_message,2000,0))>0)
  {
    write(sock,client_message,strlen(client_message));
    memset(client_message,'\0',2000);
  }

  if(read_size==0)
  {
    puts("Client disconnected");
    fflush(stdout);
  }
  else if(read_size == -1)
  {
    perror("recv failed");
  }

  close(sock);
  free(socket_desc);

  return 0;
}


int main(int argc,char *argv[])
{
  int c,clientfd,sockfd,*new_sock;
  struct sockaddr_in server,client;
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
  while((clientfd = accept(sockfd,(struct sockaddr*)&client,(socklen_t*)&c)))
  {

    puts("Connection Accepted!\n");
   
    pthread_t sniffer_thread;
    new_sock = malloc(1);
    *new_sock = clientfd;
    
    //Blocking not handled yet
    if(pthread_create(&sniffer_thread,NULL,connection_handler,(void*)new_sock)<0)
    {
       perror("could not create thread");
       return 1;
    }
    pthread_join(sniffer_thread,NULL);
    puts("Handler assigned");
  }
  if(clientfd<0)
  {
    perror("Accept failed!\n");
    return EXIT_FAILURE;
  }
  
  close(sockfd);
  return EXIT_SUCCESS;
}