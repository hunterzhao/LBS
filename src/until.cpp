#include <memory>
#include <mutex>
#include <unistd.h>
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <strings.h>
#include <arpa/inet.h>

#include "until.h"

/*
* common function
*/
/*************************方法*********************************/
void initGlog(const char* arg)
{
    google::InitGoogleLogging(arg);
    std::string home = "../log/";
    std::string info_log = home + "info_";   
    google::SetLogDestination(google::INFO, info_log.c_str());   
    std::string warning_log = home + "warning_";   
    google::SetLogDestination(google::WARNING, warning_log.c_str());   
    std::string error_log = home + "error_";   
    google::SetLogDestination(google::ERROR, error_log.c_str());   
    std::string fatal_log = home + "fatal_";   
    google::SetLogDestination(google::FATAL, fatal_log.c_str());   
    FLAGS_alsologtostderr = 1;
    FLAGS_colorlogtostderr = 1;
}

int writen(int fd, void *buff, size_t count)
{
    /* 发送消息 */
    size_t n = count;
    int nwrite = 0;
    while (n > 0 
          && (nwrite = ::write(fd, (char*)buff + count - n, n)) > 0)
    {
       n -= nwrite;
    }
    
    if (nwrite == -1 && errno != EAGAIN)
    {
       LOG(ERROR) << "write failed";
       exit(-1);
    }
    
    /* 发送数据over 指定长度数据发完或者缓冲区为满了*/
    return n;
}

int readn(int fd, void *buff, size_t count)
{
    /* 接受数据 */
    /* 循环读取fd上的数据，直到遇到EAGAIN错误*/
    size_t n = 0;
    int    nread = 0;
    while (count > 0 
          && (nread = ::read(fd, (char*)buff + n, count)) > 0) 
    {
        n += nread;
        count -= nread;
    }
    
    if (0 == nread) 
    {
        LOG(ERROR) << "peer close";
        throw 1;
    }

    if (-1 == nread && errno != EAGAIN) 
    {
        LOG(ERROR) << "read failed";
        exit(-1);
    }
    /* 接受数据over 指定长度数据收完或者缓冲区为空了*/
    return count;
}

void setNonBlock(int sock)
{
	int opts = ::fcntl(sock, F_GETFL);
	if (opts < 0)
	{
        LOG(ERROR) << "fcntl sock failed";
		exit(1);
	}
	opts = opts | O_NONBLOCK;
	if (::fcntl(sock, F_SETFL, opts) < 0)
	{
		LOG(ERROR) << "fcntl sock failed";
		exit(1);
	}
}


void resetOneShot(int epollfd, int fd)
{
	epoll_event event;
	event.data.fd = fd;
	event.events = EVENT_ET | EVENT_ONESHOT;
	::epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event);
}

void removeFd(int epollfd, int fd)
{
    ::epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, 0);
}

void addFd(int epollfd, int events, MyEvent *ev, bool one_shot)  
{  
    if ( -1 == epollfd) 
    {
      //log error
      return;
    }
    struct epoll_event epv;
    memset(&epv, 0, sizeof(epv));  
    int op;  
    epv.data.ptr = ev;  
    epv.events = events | EVENT_ET;
    if (one_shot)  epv.events |= EVENT_ONESHOT;
    if (ev->status == 1)
    {  
        op = EPOLL_CTL_MOD;  
    }  
    else 
    {  
        op = EPOLL_CTL_ADD;  
        ev->status = 1;  
    }  
    setNonBlock(ev->fd); //ET
    if(::epoll_ctl(epollfd, op, ev->fd, &epv) < 0) 
    { 
        LOG(ERROR) << "ctl error";
    } 
} 

void sendData(int fd, struct MyEvent* ev)  
{  
    /* 缓冲区可写 */
    
    /* 如果是第一个消息包，添加发送消息长度 */
    if (!ev->slice)
    {             
        uint32_t data_full_Len = ::htonl(ev->len); 
        int left = writen(fd, &data_full_Len, sizeof(uint32_t));
        assert(left == 0);
    }
    /* 发送消息本体 */
    int left = writen(fd, ev->buff + ev->index, ev->len);

    /* 还有数据？缓冲区满了？等待下次发吧*/
    if (left > 0) 
    {
        ev->len -= left;
        ev->slice = true;
        ev->index += left;
        addFd(ev->epollfd, EVENT_OUT, ev, true);
        LOG(INFO) << "send multi times";
        return; 
    }
    /* 消息发送完罗*/
    assert(left == 0);

    /* 等待下一波到来数据 */

    ev->call_back = nullptr;
    ev->resetData();
    addFd(ev->epollfd, EVENT_IN, ev, true);
}  
