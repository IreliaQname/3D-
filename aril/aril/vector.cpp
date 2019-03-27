#include "vector.h"

#define MAX0 0.0001
#define MIN0 -0.0001

vx::vx() {}

vx::vx(vec4 _pos)
{
	pos = _pos;
}
vx::vx(vec4 p, vec3 n, vec3 c, float u, float v)
{
	pos = p;
	color = c;
	nor = n;
	tex[0] = u;
	tex[1] = v;
}
bool vx::operator==(const vx&ver)
{
	if ((pos.x - ver.pos.x) >= MIN0 && (pos.x - ver.pos.x) <= MAX0 && (pos.y - ver.pos.y) >= MIN0 && (pos.y - ver.pos.y) <= MAX0)
		return true;
	else
		return false;
}
