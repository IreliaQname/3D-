#include "triangle.h"
#include "vector.h"
#include <vector>

#define YMAX 1
#define YMIX -1
#define XMAX 1
#define XMIX -1
#define ZMAX 1
#define ZMIX 0

#include <iostream>
using namespace std;

triangle::triangle() {}

triangle::triangle(vx v1, vx v2, vx v3)
{
	vert[0] = v1;
	vert[1] = v2;
	vert[2] = v3;
}
bool triangle::istriangle()
{
	bool ret = true;
	if (vert[0] == vert[1])
		ret = false;
	else if (vert[0] == vert[2])
		ret = false;
	else if (vert[1] == vert[2])
		ret = false;
	return ret;

}

vector<triangle> triangle::clip()
{
	mysort();
	vector<vx> newvert = { vert[0],vert[1],vert[2] };
	vector<triangle> ret;
	newvert = upclip(newvert);
	if (newvert.size() >= 3)
		newvert = rightclip(newvert);
	if (newvert.size() >= 3)
		newvert = downclip(newvert);
	if (newvert.size() >= 3)
		newvert = leftclip(newvert);
	if (newvert.size() >= 3)
		ret= remake(newvert);
	return ret;

}

vector<vx> triangle::upclip(vector<vx> newvert)
{
	vector<vx>ret;
	bool from, to;
	for (vector<vx>::iterator it = newvert.begin(); it != newvert.end(); it++)
	{
		vector<vx>::iterator next;
		if ((it + 1) == newvert.end())
			next = newvert.begin();
		else
			next = it + 1;
		from = true;
		to = true;
		if (it->pos.y > 1)
			from = false;
		if (next->pos.y > 1)
			to = false;
		if (from&&to)
		{
			ret.push_back(*next);
		}
		else if (from == false && to == true)
		{
			vx vert;
			vert.pos.x = it->pos.x + (YMAX - it->pos.y)*(next->pos.x - it->pos.x) / (next->pos.y - it->pos.y);
			vert.pos.y = YMAX;
			vert.pos.z = it->pos.z + (YMAX - it->pos.y)*(next->pos.z - it->pos.z) / (next->pos.y - it->pos.y);
			vert.nor = it->nor;
			vert.color.x = it->color.x + (YMAX - it->pos.y)*(next->color.x - it->color.x) / (next->pos.y - it->pos.y);
			vert.color.y = it->color.y + (YMAX - it->pos.y)*(next->color.y - it->color.y) / (next->pos.y - it->pos.y);
			vert.color.z = it->color.z + (YMAX - it->pos.y)*(next->color.z - it->color.z) / (next->pos.y - it->pos.y);
			vert.tex[0] = it->tex[0] + (YMAX - it->pos.y)*(next->tex[0] - it->tex[0]) / (next->pos.y - it->pos.y);
			vert.tex[1] = it->tex[1] + (YMAX - it->pos.y)*(next->tex[1] - it->tex[1]) / (next->pos.y - it->pos.y);
			ret.push_back(vert);
			ret.push_back(*next);
		}
		else if (from == true && to == false)
		{
			vx vert;
			vert.pos.x = it->pos.x + (YMAX - it->pos.y)*(next->pos.x - it->pos.x) / (next->pos.y - it->pos.y);
			vert.pos.y = YMAX;
			vert.pos.z = it->pos.z + (YMAX - it->pos.y)*(next->pos.z - it->pos.z) / (next->pos.y - it->pos.y);
			vert.nor = it->nor;
			vert.color.x = it->color.x + (YMAX - it->pos.y)*(next->color.x - it->color.x) / (next->pos.y - it->pos.y);
			vert.color.y = it->color.y + (YMAX - it->pos.y)*(next->color.y - it->color.y) / (next->pos.y - it->pos.y);
			vert.color.z = it->color.z + (YMAX - it->pos.y)*(next->color.z - it->color.z) / (next->pos.y - it->pos.y);
			vert.tex[0] = it->tex[0] + (YMAX - it->pos.y)*(next->tex[0] - it->tex[0]) / (next->pos.y - it->pos.y);
			vert.tex[1] = it->tex[1] + (YMAX - it->pos.y)*(next->tex[1] - it->tex[1]) / (next->pos.y - it->pos.y);
			ret.push_back(vert);
			
		}
	}
	return ret;
}

vector<vx> triangle::rightclip(vector<vx> newvert)
{
	vector<vx>ret;
	bool from, to;
	for (vector<vx>::iterator it = newvert.begin(); it != newvert.end(); it++)
	{
		vector<vx>::iterator next;
		if ((it + 1) == newvert.end())
			next = newvert.begin();
		else
			next = it + 1;
		from = true;
		to = true;
		if (it->pos.x > 1)
			from = false;
		if (next->pos.x > 1)
			to = false;
		if (from&&to)
		{
			ret.push_back(*next);
		}
		else if (from == false && to == true)
		{
			vx vert;
			
			vert.pos.y = it->pos.y + (XMAX - it->pos.x)*(next->pos.y - it->pos.y) / (next->pos.x - it->pos.x);
			vert.pos.x = XMAX;
			vert.pos.z = it->pos.z + (XMAX - it->pos.x)*(next->pos.z - it->pos.z) / (next->pos.x - it->pos.x);
			vert.nor = it->nor;
			vert.color.x = it->color.x + (XMAX - it->pos.x)*(next->color.x - it->color.x) / (next->pos.x - it->pos.x);
			vert.color.y = it->color.y + (XMAX - it->pos.x)*(next->color.y - it->color.y) / (next->pos.x - it->pos.x);
			vert.color.z = it->color.z + (XMAX - it->pos.x)*(next->color.z - it->color.z) / (next->pos.x - it->pos.x);
			vert.tex[0] = it->tex[0] + (XMAX - it->pos.x)*(next->tex[0] - it->tex[0]) / (next->pos.x - it->pos.x);
			vert.tex[1] = it->tex[1] + (XMAX - it->pos.x)*(next->tex[1] - it->tex[1]) / (next->pos.x - it->pos.x);
			ret.push_back(vert);
			ret.push_back(*next);
		}
		else if (from == true && to == false)
		{
			vx vert;
			vert.pos.y = it->pos.y + (XMAX - it->pos.x)*(next->pos.y - it->pos.y) / (next->pos.x - it->pos.x);
			vert.pos.x = XMAX;
			vert.pos.z = it->pos.z + (XMAX - it->pos.x)*(next->pos.z - it->pos.z) / (next->pos.x - it->pos.x);
			vert.nor = it->nor;
			vert.color.x = it->color.x + (XMAX - it->pos.x)*(next->color.x - it->color.x) / (next->pos.x - it->pos.x);
			vert.color.y = it->color.y + (XMAX - it->pos.x)*(next->color.y - it->color.y) / (next->pos.x - it->pos.x);
			vert.color.z = it->color.z + (XMAX - it->pos.x)*(next->color.z - it->color.z) / (next->pos.x - it->pos.x);
			vert.tex[0] = it->tex[0] + (XMAX - it->pos.x)*(next->tex[0] - it->tex[0]) / (next->pos.x - it->pos.x);
			vert.tex[1] = it->tex[1] + (XMAX - it->pos.x)*(next->tex[1] - it->tex[1]) / (next->pos.x - it->pos.x);
			ret.push_back(vert);


		}
	}
	return ret;
}

vector<vx> triangle::downclip(vector<vx> newvert)
{
	vector<vx>ret;
	bool from, to;
	for (vector<vx>::iterator it = newvert.begin(); it != newvert.end(); it++)
	{
		vector<vx>::iterator next;
		if ((it + 1) == newvert.end())
			next = newvert.begin();
		else
			next = it + 1;
		from = true;
		to = true;
		if (it->pos.y <-1)
			from = false;
		if (next->pos.y <-1)
			to = false;
		if (from&&to)
		{
			ret.push_back(*next);
		}
		else if (from == false && to == true)
		{
			vx vert;

			vert.pos.x = it->pos.x + (YMIX - it->pos.y)*(next->pos.x - it->pos.x) / (next->pos.y - it->pos.y);
			vert.pos.y = YMIX;
			vert.pos.z = it->pos.z + (YMIX - it->pos.y)*(next->pos.z - it->pos.z) / (next->pos.y - it->pos.y);
			vert.nor = it->nor;
			vert.color.x = it->color.x + (YMIX - it->pos.y)*(next->color.x - it->color.x) / (next->pos.y - it->pos.y);
			vert.color.y = it->color.y + (YMIX - it->pos.y)*(next->color.y - it->color.y) / (next->pos.y - it->pos.y);
			vert.color.z = it->color.z + (YMIX - it->pos.y)*(next->color.z - it->color.z) / (next->pos.y - it->pos.y);
			vert.tex[0] = it->tex[0] + (YMIX - it->pos.y)*(next->tex[0] - it->tex[0]) / (next->pos.y - it->pos.y);
			vert.tex[1] = it->tex[1] + (YMIX - it->pos.y)*(next->tex[1] - it->tex[1]) / (next->pos.y - it->pos.y);
			ret.push_back(vert);
			ret.push_back(*next);
		}
		else if (from == true && to == false)
		{
			vx vert;
			vert.pos.x = it->pos.x + (YMIX - it->pos.y)*(next->pos.x - it->pos.x) / (next->pos.y - it->pos.y);
			vert.pos.y = YMIX;
			vert.pos.z = it->pos.z + (YMIX - it->pos.y)*(next->pos.z - it->pos.z) / (next->pos.y - it->pos.y);
			vert.nor = it->nor;
			vert.color.x = it->color.x + (YMIX - it->pos.y)*(next->color.x - it->color.x) / (next->pos.y - it->pos.y);
			vert.color.y = it->color.y + (YMIX - it->pos.y)*(next->color.y - it->color.y) / (next->pos.y - it->pos.y);
			vert.color.z = it->color.z + (YMIX - it->pos.y)*(next->color.z - it->color.z) / (next->pos.y - it->pos.y);
			vert.tex[0] = it->tex[0] + (YMIX - it->pos.y)*(next->tex[0] - it->tex[0]) / (next->pos.y - it->pos.y);
			vert.tex[1] = it->tex[1] + (YMIX - it->pos.y)*(next->tex[1] - it->tex[1]) / (next->pos.y - it->pos.y);
			ret.push_back(vert);


		}
	}
	return ret;
}

vector<vx> triangle::leftclip(vector<vx> newvert)
{
	vector<vx>ret;
	bool from, to;
	for (vector<vx>::iterator it = newvert.begin(); it != newvert.end(); it++)
	{
		vector<vx>::iterator next;
		if ((it + 1) == newvert.end())
			next = newvert.begin();
		else
			next = it + 1;
		from = true;
		to = true;
		if (it->pos.x <-1)
			from = false;
		if (next->pos.x <-1)
			to = false;
		if (from&&to)
		{
			ret.push_back(*next);
		}
		else if (from == false && to == true)
		{
			vx vert;

			vert.pos.y = it->pos.y + (XMIX - it->pos.x)*(next->pos.y - it->pos.y) / (next->pos.x - it->pos.x);
			vert.pos.x = XMIX;
			vert.pos.z = it->pos.z + (XMIX - it->pos.x)*(next->pos.z - it->pos.z) / (next->pos.x - it->pos.x);
			vert.nor = it->nor;
			vert.color.x = it->color.x + (XMIX - it->pos.x)*(next->color.x - it->color.x) / (next->pos.x - it->pos.x);
			vert.color.y = it->color.y + (XMIX - it->pos.x)*(next->color.y - it->color.y) / (next->pos.x - it->pos.x);
			vert.color.z = it->color.z + (XMIX - it->pos.x)*(next->color.z - it->color.z) / (next->pos.x - it->pos.x);
			vert.tex[0] = it->tex[0] + (XMIX - it->pos.x)*(next->tex[0] - it->tex[0]) / (next->pos.x - it->pos.x);
			vert.tex[1] = it->tex[1] + (XMIX - it->pos.x)*(next->tex[1] - it->tex[1]) / (next->pos.x - it->pos.x);
			ret.push_back(vert);
			ret.push_back(*next);
		}
		else if (from == true && to == false)
		{
			vx vert;
			vert.pos.y = it->pos.y + (XMIX - it->pos.x)*(next->pos.y - it->pos.y) / (next->pos.x - it->pos.x);
			vert.pos.x = XMIX;
			vert.pos.z = it->pos.z + (XMIX - it->pos.x)*(next->pos.z - it->pos.z) / (next->pos.x - it->pos.x);
			vert.nor = it->nor;
			vert.color.x = it->color.x + (XMIX - it->pos.x)*(next->color.x - it->color.x) / (next->pos.x - it->pos.x);
			vert.color.y = it->color.y + (XMIX - it->pos.x)*(next->color.y - it->color.y) / (next->pos.x - it->pos.x);
			vert.color.z = it->color.z + (XMIX - it->pos.x)*(next->color.z - it->color.z) / (next->pos.x - it->pos.x);
			vert.tex[0] = it->tex[0] + (XMIX - it->pos.x)*(next->tex[0] - it->tex[0]) / (next->pos.x - it->pos.x);
			vert.tex[1] = it->tex[1] + (XMIX - it->pos.x)*(next->tex[1] - it->tex[1]) / (next->pos.x - it->pos.x);
			ret.push_back(vert);


		}
	}
	return ret;
}

vector<triangle> triangle::remake(vector<vx> newvert)
{
	vector<triangle> ret;
	vector <vx>::iterator i = newvert.begin();
	vector<vx>::iterator j;
	if (i + 1 != newvert.end())
	{
		j = i + 1;
	}
	for (; j + 1 != newvert.end(); j++)
	{
		triangle tri(*i, *j, *(j + 1));
		ret.push_back(tri);
	}
	return ret;
}

void triangle::mysort()
{
	vec4 ab = vert[0].pos - vert[1].pos;
	vec4 ac = vert[0].pos - vert[2].pos;
	vec4 cross = ab.crosspro(ac);
	if (cross.z > 0)
	{
		vx tmp = vert[0];
		vert[0] = vert[1];
		vert[1] = tmp;
	}
}