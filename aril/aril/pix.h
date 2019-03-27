#pragma once

#include <vector>
#include "vector.h"
#include "vector3.h"
using namespace std;

typedef struct
{
	int pixlx;
	int pixly;
	float depth;
	vec3 color;
	float u;
	float v;
}pixe;
class fragment
{
public:
	vector<pixe> pixes;
};
