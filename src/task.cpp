#include <stdio.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "task.h"
#include "until.h"

#define BUFFER_SIZE 2048
namespace lbs {

void Task::work()
{
   //trace log
	printf("recv data work\n");

	if (sockfd_ != -1 && epollfd_ != -1)
	{
		//error log
	}


	char buf[ BUFFER_SIZE ];
	memset( buf, '\0', BUFFER_SIZE );

	/* 循环读取fd上的数据，直到遇到EAGAIN错误*/
	while (1)
	{
		int ret = recv(sockfd_, buf, BUFFER_SIZE - 1, 0);
		if (ret == 0)
		{
            //error log
            printf("peer close socket\n");
            break;
		}
		else if ( ret < 0)
		{
			/* 缓冲区无数据 重置oneshot操作*/
			reset_oneshot( epollfd_, sockfd_);
            //trace log
			printf("read later\n");
		}
		else
		{
			/*你的包收完了么？？？*/
			printf("content %s\n", buf );
			std::string res;
			OnMessage(/*buf 包解析交给业务层*/buf, res);
            
			//返回客户端信息
			myEvent ev;
			memmove(ev.buff, res.c_str(), res.size());
			ev.call_back = sendData;
            ev.len = res.size();

			struct epoll_event epv = {0, {0}};  
		    epv.data.ptr = &ev;  
		    epv.events = EPOLLOUT | EPOLLET | EPOLLONESHOT;
            epoll_ctl(epollfd_, EPOLL_CTL_MOD, sockfd_, &epv);
           
            return;
		}
	}
	
}


}