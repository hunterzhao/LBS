#include <stdio.h>
#include <string.h>
#include <memory>

#include "task.h"

#define BUFFER_SIZE 2048
/*
* 工作线程入口
* remember keep thread safe
*/
namespace lbs {

void Task::work(JobFuncType job)
{
    std::string req(ev_->buff, ev_->len);
    std::string res;
	job(/*buf 包解析交给业务层*/req, res);
    
	/*返回客户端信息*/
    {
        std::lock_guard<std::mutex> lck(ev_->mtx_);
        ev_->resetData();
	    ::memmove(ev_->buff, res.c_str(), res.size());
        ev_->call_back = sendData;
        ev_->len = res.size();
    }
    
    addFd(ev_->epollfd, EVENT_OUT, ev_, true); /*thread safe*/
}
} // end of namespace lbs