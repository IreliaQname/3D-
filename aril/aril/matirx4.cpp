#include "vector3.h"
#include "vector4.h"
#include "matrix4.h"
#include <math.h>
#include <iostream>

#define PI 3.1415926
using namespace std;

matrix4::matrix4()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
			{
				arr[i][j] = 1;
			}
			else
				arr[i][j] = 0;
		}
	}
}

matrix4::matrix4(const float brr[], int num)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
			{
				arr[i][j] = 1;
			}
			else
				arr[i][j] = 0;
		}
	}
	if (num >= 16)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				arr[i][j] = brr[i * 4 + j];
			}
		}
	}
	else
	{
		int k;
		for (k = 0; k < num; k++)
		{
			arr[k / 4][k % 4] = brr[k];
		}
	}


}
matrix4 matrix4::operator*(const matrix4& mat)const
{
	matrix4 res;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float tmp = 0;
			for (int k = 0; k < 4; k++)
			{
				tmp = tmp + this->arr[i][k] * mat.arr[k][j];
			}
			res.arr[i][j] = tmp;
		}
	}
	return res;
}
vec4 matrix4::operator*(const vec4& vec)
{
	vec4 res;
	res.x = arr[0][0] * vec.x + arr[0][1] * vec.y + arr[0][2] * vec.z + arr[0][3] * vec.w;
	res.y = arr[1][0] * vec.x + arr[1][1] * vec.y + arr[1][2] * vec.z + arr[1][3] * vec.w;
	res.z = arr[2][0] * vec.x + arr[2][1] * vec.y + arr[2][2] * vec.z + arr[2][3] * vec.w;
	res.w = arr[3][0] * vec.x + arr[3][1] * vec.y + arr[3][2] * vec.z + arr[3][3] * vec.w;
	return res;
}
vec3 matrix4::Nor2world(const vec3 a, const matrix4 brr)
{
	float tmp = 1 / (brr.arr[0][0] * (brr.arr[1][1] * brr.arr[2][2] - brr.arr[1][2] * brr.arr[2][1]) - brr.arr[1][0] *
		(brr.arr[0][1] * brr.arr[2][2] - brr.arr[0][2] * brr.arr[2][1]) + brr.arr[2][0] * (brr.arr[0][1] *
			brr.arr[1][2] - brr.arr[1][1] * brr.arr[0][2]));
	vec3 res;
	res.x = tmp * (brr.arr[1][1] * brr.arr[2][2] - brr.arr[1][2] * brr.arr[2][1])*a.x +
		tmp * (brr.arr[1][2] * brr.arr[2][0] - brr.arr[1][0] * brr.arr[2][2])*a.y +
		tmp * (brr.arr[1][0] * brr.arr[2][1] - brr.arr[1][1] * brr.arr[2][0])*a.z;

	res.y = tmp * (brr.arr[0][2] * brr.arr[2][1] - brr.arr[0][1] * brr.arr[2][2])*a.x +
		tmp * (brr.arr[0][0] * brr.arr[2][2] - brr.arr[0][2] * brr.arr[2][0])*a.y +
		tmp * (brr.arr[0][1] * brr.arr[2][0] - brr.arr[0][0] * brr.arr[2][1])*a.z;

	res.z = tmp * (brr.arr[0][1] * brr.arr[1][2] - brr.arr[0][2] * brr.arr[1][1])*a.x +
		tmp * (brr.arr[1][0] * brr.arr[0][2] - brr.arr[0][0] * brr.arr[1][2])*a.y +
		tmp * (brr.arr[0][0] * brr.arr[1][1] - brr.arr[0][1] * brr.arr[1][0])*a.z;
	return res;
 }
matrix4 matrix4::tra(const matrix4& brr, vec3 a)
{
	float crr[] = { 1,0,0,a.x,
					0,1,0,a.y,
					0,0,1,a.z,
					0,0,0,1
	};
	int num = sizeof(crr)/sizeof(crr[0]);
	matrix4 tra(crr, num);
	return  brr*tra;
}
matrix4 matrix4::rotate(const matrix4&arr,float Q,vec3 vec)//ÈÆvecÖáÐý×ªQ
{
	float cosi = cos(Q*PI / 180), sini = sin(Q*PI / 180);
	float brr[] = { cosi + pow(vec.x,2)*(1 - cosi),vec.x*vec.y*(1 - cosi) - vec.z*sini,vec.x*vec.z*(1 - cosi) + vec.y*sini,0,
		vec.x*vec.y*(1 - cosi) + vec.z*sini,cosi + pow(vec.y,2)*(1 - cosi),vec.y*vec.z*(1 - cosi) - vec.x*sini,0,
		vec.x*vec.z*(1 - cosi) - vec.y*sini,vec.y*vec.z*(1 - cosi) + vec.x*sini,cosi + pow(vec.z,2)*(1 - cosi),0,
		0,0,0,0 };
	int num = sizeof(brr) / sizeof(brr[0]);
	matrix4 rota = matrix4(brr, num);
	return arr*rota;
 }
matrix4 matrix4::maxmin(const matrix4&arr,vec3 vec)
{
	float brr[] = { vec.x,0,0,0,
		0,vec.y,0,0,
		0,0,vec.z,0,
		0,0,0,1 };
	int num = sizeof(brr) / sizeof(brr[0]);
	matrix4 tmp = matrix4(brr, num);
	return  arr*tmp;


 }
matrix4 matrix4::orth(float l,float r,float t,float b,float n,float f)
{
	float arr[] = {
		2 / (r - l),0,0,-(r + l) / (r - l),
		0,2 / (t - b),0,-(t + b) / (t - b),
		0,0,1 / (f - n),f / (f - n),
		0,0,0,1
	};
	matrix4 res(arr, sizeof(arr) / sizeof(arr[0]));
	return res;
 }
matrix4 matrix4::project(float l, float r, float t, float b, float n, float f)
{
	float arr[] = {
		2*n/(l - r),0,-(r+l)/(r-l),0,
		0,2*n/(b - t),-(t+b)/(t-b),0, 
		0,0,n / (n - f),f*n/(n - f),
		0,0,1,0
	};
	matrix4 res(arr, sizeof(arr) / sizeof(arr[0]));
	return res;
 }