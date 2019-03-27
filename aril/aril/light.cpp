#include "light.h"
#include "vector3.h"
#include <math.h>
#include <iostream>

using namespace std;
light::light() {}

light::light(vec3 lightpos, vec3 lcolor1, vec3 a, float as, float sh, vec3 vipos1)
{
	lpos = lightpos;
	lcolor = lcolor1;
	amb = a;
	ambh = as;
	speh = sh;
	vipos = vipos1;
}
vec3 light::cal(vx ver, vec3 frg, int ramode)
{
	vec3 ldir = lpos - frg;
	ldir.fun();
	float diff = ver.nor.dot(ldir);
	if (diff < 0)diff = 0;
	vec3 diffuse = lcolor * diff;
	vec3 viewdir = vipos - frg;
	viewdir.fun();
	vec3 indir = frg - lpos;
	vec3 refl = indir - ver.nor *(indir.dot(ver.nor)) * 2;
	float spec = viewdir.dot(refl);
	if (spec < 0)spec = 0;	
	spec = pow(spec, 1); 
	vec3 specular = lcolor * speh*spec;
	vec3 res;
	if (ramode == 2)
		res = (amb * ambh + diffuse + specular)*vec3(1, 1, 1);
	else
		res = (amb * ambh + diffuse + specular)*ver.color;
	return res;
}