#ifndef _GEO_INTERFACE_H_
#define _GEO_INTERFACE_H_
#include <vector>
#include <mutex>

#include "kdtree.h"
#include "until.h"

/*
*  geo算法库服务接口
*/

namespace geo
{
class GeoInterface
{
public:
    /* 插入一堆新的位置 thread safe*/
    int insertPos(const Position& c);

    /* 插入一个新的位置 thread safe*/
    int insertPos(const std::vector<Position>& pos);

    /* 返回半径为radius内的坐标点 thread safe */
    int searchPos(const Position& c, const double radius, 
	                 std::vector<Position>& ans) const;

private:
	/* kd tree 保存数据 */
	static struct kdtree *ptree_;
	static std::mutex mtx_;
};
}

#endif