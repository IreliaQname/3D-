#include "camera.h"
#include "matrix4.h"
#include "vector3.h"

camera::camera() {}

camera::camera(vec3 pos, vec3 tar, vec3 wup)
{
	campos = pos;
	camtrat = tar;
	worldup = wup;
	camdir = campos - camtrat;
	camdir.fun();
	camright = wup.cross(camdir);
	camright.fun();
	camup = camdir.cross(camright);
	camup.fun();
}

matrix4 camera::Lookat()
{
	matrix4 res;
	float arr[] =
	{
		camright.x,camright.y,camright.z,0,
		camup.x,camup.y,camup.z,0,
		camdir.x,camdir.y,camdir.z,0,
		0,0,0,1
	};
	matrix4 tmp(arr, sizeof(arr) / sizeof(float));
	float brr[] =
	{
		1,0,0,-campos.x,
		0,1,0,-campos.y,
		0,0,1,-campos.z,
		0,0,0,1
	};
	matrix4 tmp1(brr, sizeof(brr) / sizeof(float));
	res = res * tmp*tmp1;
	return res;
}