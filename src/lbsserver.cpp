#include <sys/epoll.h>
#include <fcntl.h>  
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <assert.h>
#include <string.h>

#include <memory>
#include "lbsserver.h"
#include "until.h"
#include "task.h"

#define WAITCONN 500
#define MAX_EVENT_NUMBER 500

namespace lbs {

void LBSServer::init(int port)
{
   //初始化epollfd
   assert(-1 == epoll_fd_);
   epoll_fd_ = epoll_create(5);
   
   //初始化监听fd
   assert(-1 == listen_fd_);
   listen_fd_ = socket(AF_INET, SOCK_STREAM, 0);
   if (listen_fd_ < 0) 
        printf("ERROR opening socket");

   //测试使用，手动关闭server，避免进入timewait
   int reuse = 1;
   setsockopt(listen_fd_, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
   
   //初始化address
   bzero(&address_, sizeof( address_ ));
   address_.sin_addr.s_addr = INADDR_ANY;
   address_.sin_port = htons(port);

   //初始化内存池
   thread_pool_ptr_ = std::make_shared<ThreadPool<Task>>();
}

int LBSServer::run()
{
    int ret = bind( listen_fd_, 
    	      (struct sockaddr*)&address_, sizeof( address_ ));
    if (ret < 0)  
    	printf("ERROR on binding");

    listen(listen_fd_, WAITCONN);
    assert( epoll_fd_ != -1);  
    addfd( epoll_fd_, listen_fd_, false);
    epoll_event events[ MAX_EVENT_NUMBER ];
    while(1)
    {
    	int ret = epoll_wait(epoll_fd_, events, MAX_EVENT_NUMBER, -1);
    	if (ret < 0)
    	{
    		printf("epoll failed");
    		break;
    	}

    	for ( int i = 0; i < ret; i++ )
    	{
    		int sockfd = events[i].data.fd;
    		//std::shared_ptr<int> socket_ptr(sockfd, close_fd); //exception safe
            myEvent *ev = (struct myEvent*)events[i].data.ptr; 

    		if ( sockfd == listen_fd_)
    		{
    			/* 连接 */
    			printf("new connect\n");
                int connfd = accept( listen_fd_, nullptr, nullptr);
                addfd( epoll_fd_, connfd, true);
                client_count_++;
    		}
    		else if (events[i].events & EPOLLIN)
    		{
    			/* 数据Come */
    			printf("new data come\n");
                std::shared_ptr<Task> t = std::make_shared<Task>(epoll_fd_, sockfd);
                thread_pool_ptr_->append(t);
    		}
    		else if (events[i].events & EPOLLOUT)
    		{
                /* 数据Go */
                printf("new data go\n");
                ev->call_back(sockfd, ev);
    		}
    	}
    }
    return ret;
}

}