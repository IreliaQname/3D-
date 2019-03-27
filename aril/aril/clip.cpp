#include "clip.h"
#include <vector>
#include <iostream>
using namespace std;
clip::clip(){}

clip::clip(vector<vx> buff)
{
	for (int i = buff.size() % 3; i != 0 && (3 - i) != 0; i++)
	{
		buff.push_back(vx());
	}
	for (vector<vx>::iterator it = buff.begin(); it != buff.end(); it += 3)
	{
		triangle tri(*it, *(it + 1), *(it + 2));
		pri.push_back(tri);
	}
}
void clip::clipall()
{
	for (vector<triangle>::iterator it = pri.begin(); it != pri.end(); it++)
	{
		vector<triangle> cl = it->clip();
		for (vector<triangle>::iterator i = cl.begin(); i != cl.end(); i++)
		{
			if (i->istriangle())
			{
				cli.push_back(*i);
			}
		}
	}
	pri.clear();
}

