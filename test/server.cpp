#include <iostream>
#include "lbsserver.h"

using namespace lbs;

int main(int argc, char const *argv[])
{
	LBSServer server;
	server.init(8899);
	server.run();
	return 0;
}