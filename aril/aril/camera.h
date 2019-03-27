#pragma once

#include "vector3.h"
#include "matrix4.h"

//#define SD 1.0

enum movement
{
	FORT,
	BACK,
	LEFT,
	RIGHT,
};

class camera
{
public:
	vec3 campos;
	vec3 camtrat;
	vec3 worldup;
	vec3 camdir;
	vec3 camright;
	vec3 camup;
	camera();
	camera(vec3 p, vec3 t, vec3 u);//相机的位置，朝向，上轴
	matrix4 Lookat();//得到视图矩阵
	void upcamera()
	{
		camdir = campos - camtrat;
		camdir.fun();
		camright = worldup.cross(camdir);
		camright.fun();
		camup = camdir.cross(camright);
		camup.fun();
	}
	void mov(movement m)//移动相机
	{
		float tmp = 0.1;
		if (m == FORT)
		{
			campos = campos - (camdir*tmp);

		}
		if (m == BACK)
		{
			campos = campos + (camdir*tmp);

		}
		if (m == LEFT)
		{
			campos = campos - (camright*tmp);
		}
		if (m == RIGHT)
		{
			campos = campos + (camright*tmp);
		}
		upcamera();
	}
};
