#include "vector4.h"

vec4::vec4()
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}
vec4::vec4(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}
vec4 vec4::operator*(const float& a)
{
	vec4 res;
	res.x = x * a;
	res.y = y * a;
	res.z = z * a;
	return res;
}
vec4 vec4::operator/(const float& a)
{
	if (a == 0)
		return *this;
	vec4 res;
	res.x = x / a;
	res.y = y / a;
	res.z = z / a;
	return res;
}
vec4 vec4::crosspro(vec4 vec)
{
	if (w == 1 || vec.w == 1)
		return *this;
	vec4 res;
	res.x = y * vec.z - z * vec.y;
	res.y = z * vec.x - x * vec.z;
	res.z = x * vec.y - y * vec.x;
	return res;
}
float vec4::dotpro(vec4 vec)
{
	if (w == 1 || vec.w == 1)
		return 0;
	return x * vec.x + y * vec.y + z * vec.z;
}

vec4 vec4::operator-(const vec4&vec)
{
	if (w != vec.w)
		return *this;
	vec4 res;
	res.x = x - vec.x;
	res.y = y - vec.y;
	res.z = z - vec.z;
	res.w = 0;
	return res;
}
vec4 vec4::operator+(const vec4&vec)
{
	if (w != vec.w)
		return *this;
	vec4 res;
	res.x = x + vec.x;
	res.y = y + vec.y;
	res.z = z + vec.z;
	res.w = 0;
	return res;
}