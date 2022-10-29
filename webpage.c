#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <strings.h>

#include <sys/types.h>

#include <sys/socket.h>

#include <netinet/in.h>

#include <arpa/inet.h>

#include <unistd.h>

#include <netdb.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>

#define MAX 1024
#define PORT 80
#define SA struct sockaddr
int main(int argc, char * argv[]) {
  if (argc != 2) {
    printf("Usage: ./download [link]\n");
    return -1;
  }
  char buff[2][MAX];
  char temp[MAX], ip[MAX], name[MAX], resp[MAX];
  strcpy(buff[0], "/");
  strcpy(buff[1], argv[1]);
  strcpy(temp, argv[1]);
  printf("Host Name: %s\n", temp);
  struct hostent * h = gethostbyname(temp);
  strcpy(ip, inet_ntoa( * ((struct in_addr * ) h -> h_addr_list[0])));
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    printf("Error in creating socket...\n");
  }
  struct sockaddr_in add;
  bzero( & add, sizeof(add));
  add.sin_family = AF_INET;
  add.sin_port = htons(PORT);
  add.sin_addr.s_addr = inet_addr(ip);
  size_t len = sizeof(add);
  int c = connect(fd, (SA * ) & add, len);
  if (c == -1) {
    printf("Error in connecting...\n");
  }
  char req[MAX * MAX];
  sprintf(req, "GET %s HTTP/1.1\r\nHost: %s\r\n\r\n", buff[0], buff[1]);
  if (send(fd, req, strlen(req), 0) < 0) {
    printf("Error in sending...\n");
    return -1;
  }
  printf("Enter the file name: ");
  scanf("%[^\n]%*c", name);
  int fp = creat(name, S_IRWXU);
  int bytes;
  while ((bytes = read(fd, resp, sizeof(resp))) > 0) {
    write(fp, resp, bytes);
  }
  close(fp);
  close(fd);
  return 0;
}
