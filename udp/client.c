#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
#include<fcntl.h>

#define PORT 10000

int main(int argc, char const *argv[]) {
  int sockfd ,clilen ;
  struct sockaddr_in servaddr;
  char f[100] , b[100];
  sockfd = socket(AF_INET , SOCK_DGRAM , 0);

  bzero(&servaddr , sizeof(servaddr));

  servaddr.sin_family = AF_INET ;
  servaddr.sin_port = htons(PORT);

  printf("File name :");
  scanf("%s",f );

  clilen = sizeof(servaddr);
  sendto(sockfd , f , sizeof(f) , 0 , (struct sockaddr*)&servaddr , clilen);

  printf("Data : \n");

  while(recvfrom(sockfd , b , 100 , 0 , (struct sockaddr*)&servaddr , &clilen)!=0)
  {
    printf("%s",b);
  }
  close(sockfd);

  return 0;
}
