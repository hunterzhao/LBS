#ifndef TASK_H_
#define TASK_H_
#include <string>
#include <string.h>
/*
* 任务
*/

namespace lbs {
class Task
{
public:
	Task(int e, int s) : epollfd_(e), sockfd_(s) {}
    
    /*读取消息， 调用业务逻辑*/
    void work();
    virtual void OnMessage(const char* buf, std::string& res) 
    { 
    	res = std::string(buf, strlen(buf));
    }

	int epollfd_ = -1;
	int sockfd_ = -1;
};
} //end of namespace lbs

#endif