#pragma once
#include "vector.h"
#include <vector>

using namespace std;

class triangle
{
public:
	vx vert[3];
	triangle();
	triangle(vx, vx, vx);
	bool istriangle();
	void mysort();
	vector<vx> upclip(vector<vx>);
	vector<vx> leftclip(vector<vx>);
	vector<vx> downclip(vector<vx>);
	vector<vx> rightclip(vector<vx>);
	vector<triangle> remake(vector<vx>);
	vector<triangle> clip();
};
