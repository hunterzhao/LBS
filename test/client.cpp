#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

class Client {
public:
	int add(double x, double y) { return -1;}
	int search() { return -1;}
   
private:
    int id = 0;
};

int main(int argc, char const *argv[])
{
    int sockfd;
    struct sockaddr_in serv_addr;	

    char buffer[256];

    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
    if (sockfd < 0) {
      printf("ERROR opening socket");
      exit(1);
    }
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(8899);
   
    /* Now connect to the server */
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR connecting");
      exit(1);
    }
    bzero(buffer, 256);
    const char *s = "hello LBS";
    memcpy(buffer, s, strlen(s));
    /* Send message to the server */
    size_t n = write(sockfd, buffer, strlen(buffer));
   
    if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
    }
   
    /* Now read server response */
    bzero(buffer, 256);
    n = read(sockfd, buffer, 255);
   
    if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
    }
	
    printf("%s\n",buffer);
    return 0;
}