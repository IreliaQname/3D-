#pragma once

class vec4 {
public:
	float x;
	float y;
	float z;
	float w;
	vec4();
	vec4(float,float,float,float);
	vec4 operator*(const float&);
	vec4 operator/(const float&);
	vec4 crosspro(vec4);
	float dotpro(vec4);
	vec4 operator-(const vec4&);
	vec4 operator+(const vec4&);
};