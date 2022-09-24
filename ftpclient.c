#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<strings.h>
#include<string.h>
#include<arpa/inet.h>
#include<fcntl.h>
int main(){
	int clientsocket;
	
	clientsocket = socket(AF_INET , SOCK_STREAM , 0);
	printf("Client socket created");
	
	struct sockaddr_in clientaddress;
	
	clientaddress.sin_family = AF_INET;
	clientaddress.sin_port = 8080;
	clientaddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	int status = connect(clientsocket ,(struct sockaddr *)&clientaddress, sizeof(clientaddress));
	if(status)
		printf("\nClient socket connected!");
	
	
	char fname[1000];
	char buffer[1000];
	
	bzero(buffer, sizeof(buffer));
	bzero(fname,sizeof(fname));
	printf("\nEnter the name(path) of file to read : ");
	scanf("%s",fname);
	send(clientsocket, fname, sizeof(fname), 0);
		
	bzero(buffer, sizeof(buffer));
	recv(clientsocket, buffer, sizeof(buffer), 0);
	printf("File Contents : \n");
	int fd=open("Desktop/newfile.txt",O_RDWR|O_CREAT);
	int fd2 = write(fd,buffer,sizeof(buffer));
	printf("\nFile contents transferred to: Desktop/newfile.txt");

		

	close(fd);
	close(fd2);
	close(clientsocket);
	printf("\nDisconnected!\n");
	
	return 0;
}
