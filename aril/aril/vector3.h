#pragma once
class vec3 {
public:
	float x, y, z;
	vec3();
	vec3(float,float,float);
	vec3 operator - (const vec3&);
	vec3 operator * (const vec3&);
	vec3 operator*(const float&);
	vec3 cross(vec3);
	float dot(vec3);
	vec3 operator+(const vec3&);
	void fun();
};