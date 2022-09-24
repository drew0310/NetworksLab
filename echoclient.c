#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<strings.h>
#include<string.h>
#include<arpa/inet.h>

int main()
{
	int clientsocket,n;
	
	clientsocket = socket(AF_INET , SOCK_STREAM , 0);
	printf("Client socket created");
	
	struct sockaddr_in clientaddress;
	
	clientaddress.sin_family = AF_INET;
	clientaddress.sin_port = 8080;
	clientaddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	int status = connect(clientsocket ,(struct sockaddr *)&clientaddress, sizeof(clientaddress));
	if(status)
		printf("Client socket connected");
	
		
	char buffer[1000];
	while(strcmp(buffer,"exit"))
	{
		bzero(buffer, sizeof(buffer));
		printf("\nClient : ");
		scanf("%s",buffer);
		send(clientsocket, buffer, sizeof(buffer), 0);
		
		bzero(buffer, sizeof(buffer));
		recv(clientsocket, buffer, sizeof(buffer), 0);
		printf("Server : %s\n",buffer);
	
	}
	close(clientsocket);
	printf("\nDisconnected\n");
	
	return 0;
}
