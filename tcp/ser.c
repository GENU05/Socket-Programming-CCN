#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

#define PORT 10000

int main(int argc, char const *argv[])
{
  int i , j;
  ssize_t n;
  FILE *fp;
  int listenfd , connfd ,clilen ;
  struct sockaddr_in servaddr , clinaddr;
  char f[100] , s[100] ;

  listenfd = socket(AF_INET , SOCK_STREAM , 0);

    bzero(&servaddr , sizeof(servaddr));

  servaddr.sin_family = AF_INET ;
  servaddr.sin_port = htons(PORT) ;

  bind(listenfd , (struct sockaddr*)&servaddr , sizeof(servaddr));
  listen(listenfd , 1);

  clilen = sizeof(clinaddr);
  connfd = accept(listenfd , (struct sockaddr*)&clinaddr , &clilen);
  printf("Connection Established\n");

  read(connfd , f , 100);
  fp = fopen(f,"r");
  printf("File name : %s\n",f);

  while(fgets(s,100,fp) != NULL)
  {
    printf("%s", s);
    write(connfd,s,sizeof(s));
  }
  fclose(fp);
  close(listenfd);

  return 0;
}
