#include<stdio.h>
#include<unistd.h>
#include<netdb.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<fcntl.h>
#include<math.h>
#define PORT 8081
#define SA struct sockaddr
#include <string.h>

char *strrev(char *str)
{
	if (!str || ! *str)
	return str;
	int i = strlen(str) - 1, j = 0;
	char ch;
	while (i > j)
	{
		ch = str[i];
		str[i] = str[j];
		str[j] = ch;
		i--;j++;
	}
	return str;
}

int find_r(int m)
{
	int r = 0;
	while(pow(2, r) < m+r+1)
		r++;
	return r;
}

int powerof2(int n)
{
	int num = 1;
	while(num < n)
	num*=2;
	return (num == n);
}

char* hamming(char data[30])
{
	int m, r, count, str_count = 0;
	char hamming[30], rev_data[30];
	m = strlen(data);
	r = find_r(m);
	strcpy(rev_data, strrev(data));
	for(int ind=1; ind<=m+r+1; ind++)
	if(powerof2(ind))
	hamming[ind-1] = '0';
	else
	hamming[ind-1] = rev_data[str_count++];
	for(int i=1, count=0; count<r; i*=2, count++)
	{
		int n_one = 0;
		for(int ind = i-1; ind<m+r; ind+=i+1)
		{
			for(int k=0; k<i && ind+k < m+r; k++)
				if(hamming[ind+k] == '1')
					n_one++;
		ind+=i-1;
		}
		if(n_one%2)
		hamming[i-1] = '1';
	}
	return strrev(hamming);
}

int main()
{
	int len, flag;
	int sockfd,connfd;
	struct sockaddr_in servaddr,cliaddr;
	char buff[1024],buff1[1024];
	char str[1000];
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if (sockfd == -1)
	{
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
		
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr)))!=0)
	{
		printf("socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");
	if ((listen(sockfd, 5)) != 0)
	{
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");
	len = sizeof(cliaddr);connfd = accept(sockfd, (SA*)&cliaddr, &len);
	if (connfd< 0)
	{
		printf("server acccept failed...\n");
		exit(0);
	}
	else
		printf("server acccept the client...\n");
		
	char message[30], ham[30];
	int err_bit;
	printf("\nEnter the message: ");
	scanf("%s", message);
	strcpy(ham, hamming(message));
	printf("\nThe hamming code for the message is: %s",ham);
	printf("\nEnter the erroneous bit number: ");
	scanf("%d", &err_bit);
	int m, r;
	m = strlen(message);
	r = find_r(m);
	ham[m+r-err_bit] = (ham[m+r-err_bit] == '0')? '1': '0';
	strcpy(buff1, ham);
	flag = write(connfd,buff1,sizeof(buff1));
	printf("\nErroneous message: %s", ham);
	if(flag<0)
	{
		perror("\nMessage cannot be sent!");
		exit(1);
	}
	else
		printf("\nErroneous message sent!\n");
		
close(sockfd);
close(connfd);
return 0;
}
