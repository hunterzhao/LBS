#ifndef PROCESS_H_
#define PROCESS_H_
/*
* 这是业务行为类库
*/
namespace lbs {
class Process 
{
public:
	virtual void process() = 0;
    void setX(double x) { x_ = x;}
    void setY(double y) { y_ = y;}

protected:
	double x_;
    double y_;
    int connfd_;
    int client_id_;
};

class ProcessSearch : public Process 
{
	/*
    * IN: 一个地理位置 + 半径
    * OUT:一堆地理位置 + 状态码 通过文件描述符发送给客户端  
	*/
    virtual void process() override
    {
        //TODO 1. 传入的位置，半径，结合存储结构（lock），***判断出这个圈内有哪些客户端***
        
        //TODO 2. 返回给客户端的一个消息：消息内容为周围的客户信息
    }

    void setRadius(int radius) 
    {
    	radius_ =  radius;
    }

private:
    int radius_;  //半径
};

class ProcessAdd : public Process 
{
	/*
    * IN: 一个地理位置 + 客户端id
    * OUT:状态码，添加成功或失败 通过文件描述符发送给客户端  
	*/
	virtual void process() override
	{
        //TODO 1. 在存储结构中查询是否存在该客户
        
        //TODO 2. 存在该客户id，直接在存储结构中更新该客户的位置信息

        //TODO 2. 不存在该客户id， 在存储结构（加锁）中添加新客户的基础信息 与位置信息

        //TODO 3. 返回状态信息 
	}
}
}
#endif