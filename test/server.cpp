#include "geointerface.h"
#include "message.pb.h"
#include "lbsserver.h"
#include "until.h"

using namespace lbs;

int main(int argc, char const *argv[])
{
	initGlog(argv[0]);
	LBSServer server;
	server.init(8899);

	server.setJob([](const std::string& req, std::string& res){
		geo::GeoInterface geo;
		ReqProto req_pro;
	    ResProto res_pro;
	    assert(req.size() != 0);
		assert(req_pro.ParseFromString(req) == true);
	    
	    switch (req_pro.type()) 
	    {
	        /* 消息类型为0 insert query*/
	    	case 0:
	    	{   
	            AddReqProto add_pro = req_pro.addreq();              
	            if (geo.insertPos(Position(add_pro.x(), add_pro.y())) < 0)  /*thread safe*/
	            {
	                //log error
	                LOG(ERROR) << "insert error";
	                res_pro.set_id(1);
	                res_pro.set_code(-1);
	                assert(res_pro.SerializeToString(&res) == true);
	                return;
	            }           
	            LOG(INFO) << "insert one pos ok"; 
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
	                LOG(ERROR) << "search error: x : " << search_req.x() 
	                           << " y : " << search_req.y() 
	                           << " r : " << search_req.redius(); 
	                res_pro.set_id(1);
	                res_pro.set_code(-2);
	                assert(res_pro.SerializeToString(&res) == true);
	                return;
	            }
	            LOG(INFO) << "search one pos ok"; 
	            SearchResProto* search_res = new SearchResProto();
	            for (auto c : near_pos) 
	            {
	                NearFriend f;
	                f.set_id(-1);
	                f.set_x(c.x);
	                f.set_y(c.y);
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
	});
	
	server.run();
	return 0;
}