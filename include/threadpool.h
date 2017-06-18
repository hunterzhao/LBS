#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <thread>
#include <mutex> 
#include <memory>
#include <functional>
#include <vector>
#include <list>
#include <mutex>
#include <condition_variable>
#include <queue>

#include "nocopy.h"
/*
*  这是一个线程池
*/
namespace lbs {

template<typename T>
class ThreadPool : public NonCopyable
{
public:
	ThreadPool(int thread_number = 4, unsigned int max_requests = 10000)
    : thread_number_(thread_number), 
       max_requests_(max_requests),
       stop_(false)
    {
        if ((thread_number <= 0) || (max_requests <= 0))
        {
            // error
        }

        for (int i = 0; i < thread_number; i++) 
        {
            std::unique_ptr<std::thread> thread_ptr(new std::thread(worker, this));
            thread_ptr->detach();
            threads_array_.push_back(std::move(thread_ptr));
        }
    }

	~ThreadPool()
    {
        threads_array_.clear();
        printf("thread pool dry\n");
        stop_ = true;
    }

	/*往请求队列中添加任务*/
	bool  append(const T& request)
    {
        std::lock_guard<std::mutex> lck(mtx_);
        if ( work_queue_.size() > max_requests_ )
        {
            //echo
            return false;
        }
        work_queue_.push(request);
        data_cond_.notify_one();
        return true;
    }
    
private:

	/*工作线程运行函数，不断的从工作队列中取出任务并执行*/
	static void* worker(void* arg)
    {
        ThreadPool* pool = static_cast<ThreadPool*>(arg);
        pool->run();
        return pool;
    }

    /*所有工作线程在等待条件变量满足后争抢队列中的任务*/
	void run()
    {
        while (!stop_)
        {
            printf("线程等待中。。。\n");
            std::unique_lock<std::mutex> lk(mtx_);
            data_cond_.wait(lk, [this] {return !work_queue_.empty();});
            printf("线程接单了\n");
            T request = work_queue_.front();
            work_queue_.pop();
            request.work();
        }
    }

private:
	int thread_number_;  /*线程池中的线程数目*/
	unsigned int max_requests_;   /*请求队列中的允许的最大请求数*/
	std::vector<std::unique_ptr<std::thread>> threads_array_;  /*线程数组*/
    std::queue<T> work_queue_;  /*任务队列*/
    bool stop_;  /*是否结束线程*/
    mutable std::mutex mtx_; /*互斥量*/
    std::condition_variable data_cond_; /*条件变量*/
};

} //end of namespace lbs

#endif