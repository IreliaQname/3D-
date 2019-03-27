#pragma once
#include "vector3.h"
#include "vector4.h"

class vx
{
public:
	vec4 pos;
	vec3 color;
	vec3 nor;
	float tex[2];

	vx();
	vx(vec4);
	vx(vec4, vec3, vec3, float, float);
	bool operator==(const vx&);
};
