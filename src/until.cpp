#include "until.h"

namespace lbs {
/*************************方法*********************************/

void setnonblock(int sock)
{
	int opts = fcntl(sock, F_GETFL);
	if (opts < 0)
	{
		perror("fcntl sock GETFL");
		exit(1);
	}
	opts = opts | O_NONBLOCK;
	if (fcntl(sock, F_SETFL, opts) < 0)
	{
		perror("fcntl(sock, SETFL,opts)");
		exit(1);
	}
}


void reset_oneshot( int epollfd, int fd )
{
	epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLET | EPOLLONESHOT;
	epoll_ctl( epollfd, EPOLL_CTL_MOD, fd, &event);
}

void addfd(int epollfd, int fd, bool one_shot)
{
   if ( -1 == epollfd || -1 == fd) 
   {
      //log error
   	  return;
   }
   epoll_event event;
   event.data.fd = fd;
   event.events = EPOLLIN | EPOLLET | EPOLLRDHUP;
   if (one_shot)
   {
   	  event.events |= EPOLLONESHOT;
   } 
   epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
   setnonblock(fd); //ET
}

void removefd(int epollfd, int fd)
{
   epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, 0);
}

void modfd(int epollfd, int fd, int ev)
{
   // epoll_event event;
   // event.data.fd = fd;
   // event.events = ev | EPOLLET | EPOLLONESHOT | EPOLLRDHUP;
}

void sendData(int fd, struct myEvent* ev)  
{  
    // send data 发完了？
    int ret = send(fd, ev->buff, ev->len, 0);
    if(ret > 0)  
    {
    	//log trace
        printf("send[fd=%d], [%d<->%zu]%s\n", fd, ret, ev->len, ev->buff);        
    }  
    else  
    {  
    	//log error
        perror("send error\n");
    }  
    //
    removefd(ev->epollfd, fd);
}  

void computePos(const Position& c, double radius, std::vector<Position>& ans)
{
    
}
 
}//end of namespace lbs