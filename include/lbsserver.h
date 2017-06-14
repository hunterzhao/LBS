#ifndef LBSSERVER
#define LBSSERVER
#include <netinet/in.h>

#include <memory>
#include "threadpool.h"
#include "task.h"

#define WRITE_BUFF_SIZE 2048

namespace lbs {
class LBSServer {
public:
    LBSServer() {}
    
    ~LBSServer() {}

	 /* 初始化新接受的连接*/
    void init(int port);

	/*epoll 主循环*/
	int run();

private:	
/*所有的socket事件都注册到同一个epoll上*/
	int epoll_fd_ = -1;
	
	/*正在连接的客户数量*/
	int client_count_ = 0;

	/*该server的监听套接字 与地址*/
	int listen_fd_ = -1;

    struct sockaddr_in address_;

    // /* 读缓冲区 */
    // char readbuf_[READ_BUFF_SIZE];

    // /* 写缓冲区 */
    // char writebuf_[WRITE_BUFF_SIZE];

    /* 线程池 */
    std::shared_ptr<ThreadPool<Task>> thread_pool_ptr_;
};
}

#endif