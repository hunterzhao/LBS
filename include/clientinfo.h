#ifndef CLIENTINFO_H_
#define CLIENTINFO_H_
#include "until.h"
/*
*  客户端的信息
*/
namespace lbs {

class ClientInfo {
public:
    inline bool checkId(int client_id);

private:
	int client_id_;     //客户id
	Position now_pos_;  //当前位置
};
} //end of namespace lbs
#endif