#ifndef TASK_H_
#define TASK_H_
#include <assert.h>
#include <string>
#include <string.h>

#include "until.h"
/*
* 工作线程入口
* remember keep thread safe
*/

namespace lbs {
class Task
{
public:
	Task(myEvent* ev) 
	    : ev_(ev) {}
    
    /*读取消息， 调用业务逻辑*/
    void work();
    virtual void OnMessage(const std::string& req, std::string& res);
    
	myEvent *ev_ = nullptr;
};
} //end of namespace lbs

#endif