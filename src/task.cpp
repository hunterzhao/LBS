#include <stdio.h>
#include <string.h>
#include <memory>

#include "task.h"
#include "until.h"
#include "geointerface.h"

#include "message.pb.h"

#define BUFFER_SIZE 2048
/*
* 工作线程入口
* remember keep thread safe
*/
namespace lbs {

void Task::work()
{
    std::string req(ev_->buff, ev_->len);
    std::string res;
	OnMessage(/*buf 包解析交给业务层*/req, res);
    
	/*返回客户端信息*/
    ev_->resetData();
	::memmove(ev_->buff, res.c_str(), res.size());
    ev_->call_back = sendData;
    ev_->len = res.size();
    addFd(ev_->epollfd, EVENT_OUT, ev_, true); /*thread safe*/
}

void Task::OnMessage(const std::string& req, std::string& res) 
{ 
    geo::GeoInterface geo;
	ReqProto req_pro;
    ResProto res_pro;
    assert(req.size() != 0);
	assert(req_pro.ParseFromString(req) == true);
    
    switch (req_pro.type()) 
    {
        /* 消息类型为0 insert query*/
    	case 2:
    	{   
            AddReqProto add_pro = req_pro.addreq();              
            if (geo.insertPos(Position(add_pro.x(), add_pro.y())) < 0)  /*thread safe*/
            {
                //log error
                printf("insert error\n");
                res_pro.set_id(1);
                res_pro.set_code(-1);
                assert(res_pro.SerializeToString(&res) == true);
                return;
            }           
            printf("insert one pos ok\n"); 
		    res_pro.set_id(1);
		    res_pro.set_code(1);
		    assert(res_pro.SerializeToString(&res) == true);
    	} 
    	break;
        /* 消息类型为1 search query*/
    	case 1:
    	{
    		SearchReqProto search_req = req_pro.searchreq();
            std::vector<Position> near_pos;
            if  (!geo.searchPos(Position(search_req.x(), search_req.y()), 
                      search_req.redius(), near_pos)) /*thread safe*/
            {
                //log error
                printf("search error: x : %f, y : %f r : %f\n", 
                       search_req.x(), search_req.y(), search_req.redius());
                res_pro.set_id(1);
                res_pro.set_code(-2);
                assert(res_pro.SerializeToString(&res) == true);
                return;
            }
            printf("search one pos ok\n"); 
            SearchResProto* search_res = new SearchResProto();
            for (auto c : near_pos) 
            {
                NearFriend f;
                f.set_id(-1);
                f.set_x(c.x_);
                f.set_y(c.y_);
                *(search_res->add_friends()) = f;
            }
            res_pro.set_id(1);
            res_pro.set_type(1);
            res_pro.set_code(1);
            res_pro.set_allocated_searchres(search_res);
            assert(res_pro.SerializeToString(&res) == true);
    	}
        break;
    }
	
}
}