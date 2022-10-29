#include <netdb.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<fcntl.h>
#include<math.h>
#define PORT 8081
#define SA struct sockaddr

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
	i--;
	j++;
	}
	return str;
}

int bin_to_dec(char bin_str[30])
{
	int bin = atol(bin_str);
	int dec = 0;
	while(bin > 0)
	{
		dec += 2*(bin%10);
		bin/=10;
	}
	return dec;
}

int find_r(int mPlusr)
{
	int r = 0;
	while(pow(2, r) < mPlusr+1)
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
	int mPlusr, r, count, str_count = 0;
	char error[30], rev_data[30];
	mPlusr = strlen(data);
	r = find_r(mPlusr);
	strcpy(rev_data, strrev(data));
	for(int i=1, count=0; count<r; i*=2, count++)
	{
		int n_one = 0;
		for(int ind = i-1; ind<mPlusr; ind+=i+1)
		{
			for(int k=0; k<i && ind+k < mPlusr; k++)
				if(data[ind+k] == '1')
					n_one++;
			ind+=i-1;
		}
	error[count] = (n_one%2)? '1': '0';
	}
	return strrev(error);
}

void ham_to_msg(char *ham, char *msg, int len)
{
	char rev[30];
	strcpy(rev, strrev(ham));int count = 0;
	for(int i=1; i<=len; i++)
	if(!powerof2(i))
		msg[count++] = rev[i-1];
	msg[count] = '\0';
	strcpy(msg, strrev(msg));
}

int main()
{
	int len;
	int sockfd,newfd,cli1,cli2,fp;
	struct sockaddr_in servaddr,cliaddr;
	char str[1000];
	char buff1[1024],buff2[1024],c[100];
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if (sockfd == -1)
	{
		printf("socket creation failed...\n");
		exit(0);
	}
	else
	printf("Socket successfully created..\n");
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servaddr.sin_port=htons(PORT);
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))!=0)
	{
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");
	cli2=read(sockfd,buff2,sizeof(buff2));
	if(cli2<0)
	{
	perror("Message can't be received.");
	exit(1);
	}
	else
		printf("\nMessage received!");
	char msg[30];strcpy(msg, buff2);
	printf("\nReceived message : %s", msg);
	char temp[30];
	strcpy(temp, msg);
	len = strlen(msg);
	char bin_err_bit[30];
	strcpy(bin_err_bit, hamming(msg));
	int err_bit;
	err_bit = bin_to_dec(bin_err_bit);
	printf("\nErroneous bit number in binary: %s",bin_err_bit);
	printf("\nErroneous bit number in decimal: %d", err_bit);
	temp[len-err_bit] = (temp[len-err_bit] == '0')? '1': '0';
	printf("\nCorrected message: %s", temp);
	char org[30];
	ham_to_msg(temp, org, len);
	printf("\nDecoded original message: %s\n", org);
	close(fp);
	close(sockfd);
	close(newfd);
	return 0;
}
