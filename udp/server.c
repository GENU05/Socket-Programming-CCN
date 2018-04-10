#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
#include<fcntl.h>

#define PORT 10000

int main(int argc, char const *argv[]) {
  int sd , connfd , clilen ;
  struct sockaddr_in servaddr , clinaddr;
  FILE *fp;
  char buff[100] , filebuffer[100];

  sd = socket(AF_INET , SOCK_DGRAM , 0);
  bzero(&servaddr , sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);

  bind(sd ,(struct sockaddr*)&servaddr , sizeof(servaddr) );

  clilen = sizeof(clinaddr);
  recvfrom(sd , buff , 100 , 0 , (struct sockaddr*)&clinaddr , &clilen);

  fp = fopen(buff , "r");

  while(fgets(filebuffer , 100 ,fp)!=0)
  {
    sendto(sd , filebuffer , 100 , 0 , (struct sockaddr*)&clinaddr , clilen);
  }
  fclose(fp);
  close(sd);
  return 0;
}
