#ifndef LBSSERVER
#define LBSSERVER
#include <netinet/in.h>
#include <memory>

#include "threadpool.h"
#include "task.h"
#include "until.h"

#define WAITCONN 500
#define MAX_EVENT_NUMBER 500

namespace lbs {
class LBSServer {
public:
    LBSServer() {}
    
    ~LBSServer() {}

	 /* 初始化新接受的连接*/
    void init(int port);

	/* epoll 主循环*/
	int run();
    
    /* 注入业务逻辑接口 */
    void setJob(JobFuncType job);

private:	
/*所有的socket事件都注册到同一个epoll上*/
	int epoll_fd_ = -1;
	
	/*正在连接的客户数量*/
	int client_count_ = 0;

	/*该server的监听套接字 与地址*/
	int listen_fd_ = -1;

    struct sockaddr_in address_;

    /* 线程池 */
    std::shared_ptr<ThreadPool<Task>> thread_pool_ptr_;
    
    /* event 池*/
    MyEvent events_pool_[MAX_EVENT_NUMBER + 1];
};
}

#endif