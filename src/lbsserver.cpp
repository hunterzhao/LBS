#include <sys/epoll.h>
#include <fcntl.h>  
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <memory>

#include "lbsserver.h"
#include "until.h"
#include "task.h"

namespace lbs {

void LBSServer::init(int port)
{
    /* 初始化epollfd */
    assert(-1 == epoll_fd_);
    epoll_fd_ = ::epoll_create(1);
    if (epoll_fd_ < 0)
        LOG(ERROR) << "init epoll error";

    /* 初始化监听fd */
    assert(-1 == listen_fd_);
    listen_fd_ = ::socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd_ < 0) 
        LOG(ERROR) << "listern socket error";

    /* 测试使用，手动关闭server，避免进入timewait */
    int reuse = 1;
    ::setsockopt(listen_fd_, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
   
    //初始化address
    ::bzero(&address_, sizeof(address_));
    address_.sin_addr.s_addr = INADDR_ANY;
    address_.sin_port = htons(port);
   
    /* 初始化线程池 */
    thread_pool_ptr_.reset(new ThreadPool<Task>(4));
   
    /* 初始化event池 */
    for(int i = 0; i < MAX_EVENT_NUMBER; i++)  
        events_pool_[i].epollfd = epoll_fd_;
    LOG(INFO) << "server init over";
}

int LBSServer::run()
{
    int ret = ::bind(listen_fd_, 
    	      (struct sockaddr*)&address_, sizeof(address_));
    if (ret < 0)
        LOG(ERROR) << "binding error";

    ::listen(listen_fd_, WAITCONN);
    assert(epoll_fd_ != -1); 
    
    /*将listen fd 添加到epoll*/
    MyEvent* ev = &events_pool_[MAX_EVENT_NUMBER]; 
    ev->fd = listen_fd_;
    addFd(epoll_fd_, EVENT_IN, ev, false);

    epoll_event events[MAX_EVENT_NUMBER];
    LOG(INFO) << "server running";
    while (1)
    {
      	int ret = ::epoll_wait(epoll_fd_, events, MAX_EVENT_NUMBER, 1000);
      	if (ret < 0)
      	{
            LOG(ERROR) << "epoll wait failed";
        		break;
      	}
      	for (int i = 0; i < ret; i++)
      	{
        		//std::shared_ptr<int> socket_ptr(sockfd, close_fd); //exception safe
            MyEvent* ev = static_cast<MyEvent*>(events[i].data.ptr); 

        		if (ev->fd == listen_fd_)
        		{
                int connfd = ::accept(listen_fd_, nullptr, nullptr);
                if (connfd < 0) 
                { 
                    LOG(ERROR) << "conn accept failed";
                    break;
                }
                /*将listen fd 添加到epoll*/
                for (i = 0; i < MAX_EVENT_NUMBER; i++)  
                {  
                    if (events_pool_[i].status == 0)  
                        break;  
                }  
                events_pool_[i].fd = connfd;
                addFd(epoll_fd_, EPOLLIN, &events_pool_[i], true);
                client_count_++;
        		}
        		else if (events[i].events & EPOLLIN)
        		{
                try {
              			/* 数据Come */
                    uint32_t data_full_len;
                    int left = 0;
                    if (!ev->slice) 
                    {
                        left = readn(ev->fd, &data_full_len, sizeof(uint32_t));
                        data_full_len = ::ntohl(data_full_len);
                        ev->len = data_full_len;
                        assert(ev->len != 0);
                    }
                    left = readn(ev->fd, ev->buff + ev->index, ev->len);
                    
                    /* 消息没有接受完*/
                    if (left > 0)
                    {
                        ev->slice = true;
                        ev->len = left;
                        ev->index = data_full_len - left;
                        addFd(epoll_fd_, EPOLLIN, ev, true);
                        LOG(INFO) << "recv multi times";
                        continue;
                    }
                     /* 数据确认接受完毕*/
                    assert(left == 0);
                    ev->len = data_full_len;
                } 
                catch(...) 
                {
                    /* 对端关闭了连接 */
                    ::close(ev->fd);
                    removeFd(ev->epollfd, ev->fd);
                    client_count_--;
                    continue;
                }
                    
                Task t = Task(ev);
                thread_pool_ptr_->append(t);
        		}
        		else if (events[i].events & EPOLLOUT)
        		{
                /* 数据Go */
                void (*cb)(int fd, struct MyEvent*);
                {
                    std::lock_guard<std::mutex> lck(ev->mtx_);
                    cb = ev->call_back;
                }
                cb(ev->fd, ev);
            }
      	}   
    }
    ::close(epoll_fd_);
    ::close(listen_fd_);
    return ret;
}

void LBSServer::setJob(JobFuncType job)
{
    thread_pool_ptr_->setJob(job);
}
}