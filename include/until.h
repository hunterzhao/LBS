#ifndef UNTIL_H_
#define UNTIL_H_
#include <sys/epoll.h>
#include <fcntl.h> 
#include <sys/types.h>
#include <sys/socket.h>

#include <functional>
#include <vector>
#define BUFF_SIZE 2048

namespace lbs {
/*************************结构*********************************/
/* 
* 位置 
*/
struct Position
{
   double x_;
   double y_;
};

struct myEvent
{
   int epollfd = -1;
   char buff[ BUFF_SIZE ];
   size_t len;
   std::function<void(int, struct myEvent*)> call_back;
};
/*************************方法*********************************/


/*
* 关闭套接字
*/
// void close_fd(int fd)
// {
// 	close(fd);
// }


/* 将套接字设置为非阻塞模式 */
extern void setnonblock(int sock);

/*重置oneshot*/
extern void reset_oneshot( int epollfd, int fd );

/*添加，默认one_shot, 多线程*/
extern void addfd(int epollfd, int fd, bool one_shot = true);

/*删除*/
extern void removefd(int epollfd, int fd);

/*修改*/
extern void modfd(int epollfd, int fd, int ev);

/*发送回调*/
extern void sendData(int fd, struct myEvent* ev);
 
/*
* 返回半径为radius内的坐标点
* unit test 重点对象
*/
extern void computePos(const Position& c, double radius, std::vector<Position>& ans);

}//end of namespace lbs

#endif