#pragma once
#include "vector3.h"
#include "vector4.h"

class matrix4 {
public:
	float arr[4][4];
	matrix4();
	matrix4(const float[],int );
	vec4 operator*(const vec4& );
	matrix4 operator*(const matrix4&)const;
	static vec3 Nor2world(const vec3,const matrix4);
	static matrix4 tra(const matrix4&,vec3);
	static matrix4 rotate(const matrix4&,float,vec3);
	static matrix4 maxmin(const matrix4&,vec3);
	static matrix4 orth(float,float,float,float,float,float);
	static matrix4 project(float, float,float,float,float,float);
};
