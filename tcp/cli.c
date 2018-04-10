#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>

#define PORT 10000

 int main(int argc, char const *argv[]) {
  int i,j;
  ssize_t n ;
  int sockfd ;
  struct sockaddr_in servaddr;
  char filename[100] , recvline[100];

  sockfd = socket(AF_INET , SOCK_STREAM , 0);
  bzero(&servaddr , sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);

  inet_pton(AF_INET , argv[1] , &servaddr.sin_family);

  connect(sockfd , (struct sockaddr*)&servaddr , sizeof(servaddr));

  printf("Filename: ");
  scanf("%s",filename);

  write(sockfd , filename , sizeof(filename));

  printf("Data : \n" );

  while(read(sockfd , recvline , 100 )!=0)
  {
    fputs(recvline , stdout);
  }
  close(sockfd);
  return 0;
}
