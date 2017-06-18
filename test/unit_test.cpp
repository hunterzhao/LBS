#include <vector>
#include <iostream>
#include "until.h"

/*
* test search & add function
*/


using namespace std;

bool test_insert()
{
	vector<Position> s; 
	s.push_back(Position(113.2, 116.2));
	s.push_back(Position(192.2, 170.6));
	s.push_back(Position(192.4, 170.4));
	s.push_back(Position(200.7, 370.6));
    insertPos(s);
    return true;
}

bool test_search()
{
	Position p(192.0, 170.7);
    vector<Position> ans;
    searchPos(p, 2.0f, ans);
    for (auto c : ans) 
       cout << c.x_ << " : " << c.y_ << endl;
   return true;
}

int main()
{
	test_insert();
	test_search();  
}