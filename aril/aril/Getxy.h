#pragma once
#include "vector3.h"
#include "matrix4.h"
#include "vector4.h"
#include "vector.h"
#include "light.h"
using namespace std;
#include <vector>

class getxy
{
public:
	vector<vx> buff;
	getxy();
	getxy(const vec3[], int);
	void colorver(light, matrix4, int);
	void transform(const matrix4&, const matrix4&, const matrix4&);//变到投影坐标
};
