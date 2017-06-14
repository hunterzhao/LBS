#include "clientinfo.h"

namespace lbs {

bool ClientInfo::checkId(int client_id) 
{
   return client_id == client_id_;
}


} //end of namespace lbs