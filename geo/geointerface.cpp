#include "assert.h"
#include "geointerface.h"

namespace geo
{
struct kdtree *GeoInterface::ptree_ = kd_create(2);
std::mutex GeoInterface::mtx_; 

int GeoInterface::insertPos(const Position& c)
{
    std::lock_guard<std::mutex> lck(mtx_);
    assert(kd_insert3(ptree_, c.x_, c.y_, 0.0f, nullptr) == 0);
    return 1;
}

int GeoInterface::insertPos(const std::vector<Position>& pos)
{
    std::lock_guard<std::mutex> lck(mtx_);
    for (auto c : pos) 
    {
       assert(kd_insert3(ptree_, c.x_, c.y_, 0.0f, nullptr) == 0);
    }
    return 1;
}

int GeoInterface::searchPos(const Position& c, const double radius, 
              std::vector<Position>& ans) const
{
    double pt[3] = { c.x_, c.y_, 0.0f };
    struct kdres *results = kd_nearest_range(ptree_, pt, radius);
    
    /*没有满足调节的坐标*/
    if (kd_res_size(results) == 0)
    {
        printf("kd is empty\n");
        return -1;
    }

    /* 获取数据 */
    while (!kd_res_end(results)) {
        double pos[3] = {0.0f, 0.0f, 0.0f};
     
        kd_res_item(results, pos);
        ans.push_back(Position(pos[0], pos[1]));
        kd_res_next(results);
    }

    /* free data */
    kd_res_free(results);
    return 1;
}
}