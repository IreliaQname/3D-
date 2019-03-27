#include <vector>
#include "vector.h"
#include "vector3.h"
#include "Getxy.h"
#include "vector4.h"
using namespace std;
getxy::getxy() {}

getxy::getxy(const vec3 verti[], int num)
{
	for (int i = 0; i < num; i += 4)
	{
		vx v(vec4(verti[i].x, verti[i].y, verti[i].z, 1.0), verti[i+1], verti[i + 2], verti[i + 3].x, verti[i + 3].y);
		buff.push_back(v);
	}
}

void getxy::colorver(light shader, matrix4 model, int rast)
{
	for (vector<vx>::iterator it = buff.begin(); it != buff.end(); it++)
	{
		it->nor = matrix4::Nor2world(it->nor, model);
		vec4 worldcoor = model * it->pos;
		vec3 fragpos(worldcoor.x, worldcoor.y, worldcoor.z);
		it->color = shader.cal(*it, fragpos, rast);
	}
}

void getxy::transform(const matrix4& model, const matrix4& view, const matrix4& pro)
{
	matrix4 trans = pro*view*model;
	for (vector<vx>::iterator it = buff.begin(); it != buff.end(); it++)
	{
		it->pos = trans * it->pos;

		it->pos = it->pos / it->pos.w;
	}
}