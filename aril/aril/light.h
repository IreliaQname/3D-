#pragma once
#include "vector3.h"
#include "vector.h"

class light
{
public:
	vec3 lpos;
	vec3 lcolor;
	vec3 amb;
	float ambh;
	float speh;
	vec3 vipos;
	light();
	light(vec3, vec3, vec3,  float, float, vec3);
	vec3 cal(vx, vec3, int);
};