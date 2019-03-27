#pragma once
#include <vector>
#include "vector.h"
#include "triangle.h"
using namespace std;
//ͼԪ
class clip
{
public:
	vector<triangle> pri;
	vector<triangle> cli;
	clip();
	clip(vector<vx>);
	void clipall();
};
