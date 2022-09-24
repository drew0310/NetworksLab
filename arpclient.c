#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
typedef struct
{
char d_ip[20];
char s_ip[20];
char s_mac[20];
}packet;
int main(int argc,char **argv)
{
int len;
int sockfd,n;
packet *p=malloc(sizeof(packet));

struct sockaddr_in servaddr,cliaddr;
char ip[20],mac[20],data[20];
sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd<0)
perror("\n cannot create socket");
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
servaddr.sin_port=htons(7228);
if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
printf("\n Connection error\n");
printf("\n IP address : ");
scanf("%[^\n]%*c",ip);
printf(" Mac address : ");
scanf("%[^\n]%*c",mac);
n=recv(sockfd,p,sizeof(*p),0);
printf("\n ARP Request received :");
printf("\n %s | %s | %s\n",p->s_ip,p->s_mac,p->d_ip);
if(strcmp(p->d_ip,ip)==0)
{
printf("\n IP Addresses Match");
n=send(sockfd,mac,sizeof(mac),0);
printf("\n ARP Reply sent :");
printf("\n %s | %s | %s | %s\n",p->s_ip,p->s_mac,p->d_ip,mac);
n=recv(sockfd,p,sizeof(*p),0);
n=recv(sockfd,data,sizeof(data),0);
printf("\n Received Packet :");
printf("\n %s | %s | %s | %s | %s\n",p->s_ip,p->s_mac,p->d_ip,mac,data);
}
else
printf("\n IP Addresses do not match\n");
printf("\n");
return 0;
}
