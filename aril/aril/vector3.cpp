#include "vector3.h"
#include <math.h>

vec3::vec3()
{
	x = 0;
	y = 0;
	z = 0;
	
}
vec3::vec3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
	
}
vec3 vec3::operator-(const vec3& a)
{
	vec3 res;
	res.x = this->x - a.x;
	res.y = this->y - a.y;
	res.z = this->z - a.z;
	return res;
}
vec3 vec3::operator*(const vec3& a)
{
	vec3 res;
	res.x = this->x * a.x;
	res.y = this->y * a.y;
	res.z = this->z * a.z;
	return res;
}
vec3 vec3::operator*(const float& _a)
{
	vec3 res;
	res.x = this->x * _a;
	res.y = this->y * _a;
	res.z = this->z * _a;
	return res;
}
void vec3::fun()
{
	float flag = pow(pow(x,2)+pow(y,2)+pow(z,2),0.5);
	if (flag != 0)
	{
		x = x / flag;
		y = y / flag;
		z = z / flag;
	}
}

vec3 vec3::cross(vec3 vec)//²æ³Ë
{
	vec3 res;
	res.x = y * vec.z - z * vec.y;
	res.y = z * vec.x - x * vec.z;
	res.z = x * vec.y - y * vec.x;
	return res;
}
float vec3::dot(vec3 vec)//µã³Ë
{
	return x * vec.x + y * vec.y + z * vec.z;
}
vec3 vec3::operator+(const vec3& vec)
{
	vec3 res;
	res.x = this->x + vec.x;
	res.y = this->y + vec.y;
	res.z = this->z + vec.z;
	return res;
}