#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/tcp.h>

#include <string>
#include "until.h"
#include "message.pb.h"

bool sendAndRecv(const std::string& str, int fd, std::string& ans) 
{
  /* Now send server resquest */
  char buffer[1024];
  bzero(buffer, 1024);

  ::memcpy(buffer, str.c_str(), str.size());
  
  /* 发送消息长度 */
  size_t dataSize = str.size(); 
  uint32_t dataSendLen = htonl(dataSize);
  int n = ::write(fd, &dataSendLen, sizeof(uint32_t));
  if (n < 0) 
  {
    perror("ERROR writing to socket");
    return false;
  }
  
  /* 1 */
   int index = 0;
   n = ::write(fd, buffer + index, 10); index += 10;
   sleep(0.5);
   n = ::write(fd, buffer + index, 10); index += 10;
   sleep(0.5);
   n = ::write(fd, buffer + index, dataSize - 20);
 // n = ::write(fd, buffer, dataSize);
  
  if (n < 0) 
  {
    perror("ERROR writing to socket");
    return false;
  }

  printf("wait return message\n");

  /* 读取头 */
  uint32_t dataRecvLen;
  n = ::read(fd, &dataRecvLen, sizeof(uint32_t));
  if (n < 0) 
  {
    perror("ERROR writing to socket");
    return false;
  }
  size_t recvLen = ::ntohl(dataRecvLen);
  
  /* Now read server response */
  ::bzero(buffer, 1024);
  
  n = ::read(fd, buffer, recvLen);
  if (n < 0) 
  {
    perror("ERROR reading from socket");
    return false;
  }
  ans = std::string(buffer, recvLen);

  return true;
}

void testReqAdd(int fd, double x, double y)
{
    lbs::ReqProto req; 
   
    req.set_type(0);  //message type 2
    req.set_id(1);  //message client id 统一为 1

    lbs::AddReqProto* add = new lbs::AddReqProto();
    add->set_x(x);
    add->set_y(y);

    req.set_allocated_addreq(add);
    std::string str;
    std::string ans;
    assert(req.SerializeToString(&str) == true);

    assert(sendAndRecv(str, fd, ans) == true);
    
    lbs::ResProto res;
    assert(res.ParseFromString(ans) == true);
    printf("code %d \n", res.code());
    assert(res.code() == 1);
    printf("Add Correct\n");
}

void testReqSearch(int fd, double x, double y, double radius)
{
    lbs::ReqProto req; 
   
    req.set_type(1);  //message type 1
    req.set_id(1);  //message client id 统一为 1
  
    lbs::SearchReqProto* search = new lbs::SearchReqProto(); 
    search->set_x(x);
    search->set_y(y);
    search->set_redius(radius);

    req.set_allocated_searchreq(search); 
    std::string str;
    std::string ans;
    assert(req.SerializeToString(&str) == true);

    assert(sendAndRecv(str, fd, ans) == true);

    lbs::ResProto res;
    assert(res.ParseFromString(ans) == true);
    assert(res.code() == 1);
    printf("Search Correct\n");
    lbs::SearchResProto searchres = res.searchres();
    for (int i = 0; i < searchres.friends_size(); i++) 
    {
       printf("friend pos x : %f y : %f \n", 
               searchres.friends(i).x(), searchres.friends(i).y());
    }
}

int main(int argc, char const *argv[])
{
    int sockfd;
    struct sockaddr_in serv_addr;

    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0) 
    {
      printf("ERROR opening socket");
      exit(1);
    }
    
    /* 关闭 nagle*/
    int flag = 1;
    int ret = setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, (char *)&flag, sizeof(flag));
    if (ret == -1)
    {
       printf("Couldn't setsockopt(TCP_NODELAY)\n");
       exit(-1);
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
    
    testReqAdd(sockfd, 113.2, 116.2);
    testReqAdd(sockfd, 192.2, 170.6);
    testReqAdd(sockfd, 192.4, 170.4);
    testReqAdd(sockfd, 200.7, 370.6);

    testReqSearch(sockfd, 192.0, 170.7, 2.0f);

    close(sockfd);
    return 0;
}