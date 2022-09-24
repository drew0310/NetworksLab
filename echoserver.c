#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<strings.h>
#include<string.h>
#include<arpa/inet.h>
int main()
{
	char buffer[1000];
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM , 0);
	
	printf("Server created ");
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = 8080;
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	
	bind(server_socket , (struct sockaddr*)&server_address, sizeof(server_address));
	printf("\nSocket and port are bound ");
	listen(server_socket, 5);
	printf("\nListening for clients....");
	int client_socket; 
	client_socket = accept(server_socket , NULL, NULL);
	
	while(strcmp(buffer,"exit"))
	{
		bzero(buffer, sizeof(buffer));
		printf("\nClient : ");
		
		recv(client_socket, buffer, sizeof(buffer),0);
		printf("%s",buffer);
		send(client_socket , buffer , sizeof(buffer), 0 );
		
	}
	close(server_socket);
	printf("\nClient disconnected\n");
	
	return 0;
}
