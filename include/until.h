#ifndef UNTIL_H_
#define UNTIL_H_
#include <sys/epoll.h>
#include <fcntl.h> 
#include <sys/types.h>
#include <sys/socket.h>

#include <string.h>
#include <functional>
#include <vector>
#include <mutex>

#include <glog/logging.h>

#define BUFF_SIZE 1024
/*************************类型*********************************/
typedef std::function<void(const std::string& req, std::string& res)> JobFuncType;

/*************************结构*********************************/

/* 
* 位置 
*/
struct Position
{
   double x;
   double y;
   int    id;
   Position(double x_r, double y_r) :x(x_r), y(y_r) {}
};

struct MyEvent
{
public:
   int    fd = -1;
   int    epollfd = -1;
   char   buff[BUFF_SIZE];
   size_t len = 0;       /* 消息长度 */
   size_t index = 0;     /* 发送起始位置，可能需要发送/接受 多次 */
   bool   slice = false;   /* 发生分包*/
   void   (*call_back)(int fd, struct MyEvent*); 
   int    status = 0;       /* 该事件已经被添加到内核中*/
   std::mutex mtx_;    /* 主线程工作线程都会修改该结构*/

   MyEvent() {}
   MyEvent(int f, int e) : fd(f), epollfd(e) {}

   void resetData() 
   {
     	::bzero(buff, BUFF_SIZE);
      slice = false;
      index = 0;
     	len = 0;  
   }
};

enum 
{
    EVENT_IN   = EPOLLIN,
    EVENT_OUT  = EPOLLOUT,
    EVENT_ERR  = EPOLLERR,
    EVENT_HUB  = EPOLLHUP,
    EVENT_ET   = EPOLLET,
    EVENT_ONESHOT = EPOLLONESHOT
};
/*************************方法*********************************/


/*
* 关闭套接字
*/
// void close_fd(int fd)
// {
// 	close(fd);
// }
/* 初始化glog*/
extern void initGlog(const char* arg);

/* 发送count长的数据包，并添加长度包头 */
extern int writen(int fd, void *buff, size_t count);

/* 接受count长的数据包*/
extern int readn(int fd, void *buff, size_t count);

/* 将套接字设置为非阻塞模式 */
extern void setNonBlock(int sock);

/* 重置oneshot*/
extern void resetOneShot(int epollfd, int fd);

/* 添加或修改epollfd，oneshoot make thread safe*/
extern void addFd(int epollfd, int events, MyEvent *ev, bool one_shot = true);

/* 删除 */
extern void removeFd(int epollfd, int fd);

/* 修改 */
extern void modFd(int epollfd, int fd, int ev);

/* 发送回调 oneshoot make thread safe*/
extern void sendData(int fd, struct MyEvent* ev);

#endif