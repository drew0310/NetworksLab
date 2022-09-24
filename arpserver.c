#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
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
int sockfd,newfd,n;
packet *p=malloc(sizeof(packet));
struct sockaddr_in servaddr,cliaddr;
char d_mac[20];
char data[20];
pid_t child;

sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd<0)
perror("cannot create socket");
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=INADDR_ANY;
servaddr.sin_port=htons(7228);
if(bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
perror("Bind error");
listen(sockfd,2);
len=sizeof(cliaddr);
printf("\n Enter the details of the packet received : ");
printf("\n Destination IP : ");
scanf("%[^\n]%*c",p->d_ip);
printf(" Source IP : ");
scanf("%[^\n]%*c",p->s_ip);
printf(" Source MAC : ");
scanf("%[^\n]%*c",p->s_mac);
printf(" 16 bit data : ");
scanf("%[^\n]%*c",data);
printf("\n Developing the ARP Request packet");
printf("\n %s | %s | %s\n",p->s_ip,p->s_mac,p->d_ip);
printf("\n ARP Request packet is broadcasted");
printf("\n Waiting for reply...\n");
while(1)
{
newfd=accept(sockfd,(struct sockaddr*)&cliaddr,&len);
if(newfd<0)
break;
if((child=fork())==0)
{
n=send(newfd,p,sizeof(*p),0);
if(recv(newfd,d_mac,sizeof(d_mac),0)>0)
{
printf("\n ARP Reply Received");
printf("\n %s | %s | %s | %s\n",p->s_ip,p->s_mac,p->d_ip,d_mac);

printf("\n Sending packet to : %s",d_mac);
printf("\n Packet sent :");

printf("\n %s | %s | %s | %s | %s\n",p->s_ip,p->s_mac,p->d_ip,d_mac,data);

n=send(newfd,p,sizeof(*p),0);
n=send(newfd,data,sizeof(data),0);
break;
}
}
}
close(sockfd);
close(newfd);
return 0;
}
