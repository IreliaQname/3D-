#pragma once
#include "pix.h"
#include "triangle.h"
#include <vector>
#include "vector3.h"
#include <glut/glut.h>
//¹âÕ¤Æ÷
using namespace std;
enum rastert
{
	LINE,
	FILL,
	TEXTURE
};

typedef struct edge
{
	float x;
	float dx;
	int ymax;
	edge* next;
	vec3 color;
	float dcolorx;
	float dcolory;
	float dcolorz;
	float depth;
	float dz;
	float dU;
	float dV;
	float tex[2];

}edge;

class drogn
{
public:
	vector<fragment> fragments;
	pixe** framebuff;
	drogn(int, int);
	~drogn()
	{
		for (int i = 0; i < shight; i++)
		{
			delete[]framebuff[i];
		}
		delete[]framebuff;
		framebuff = NULL;
	}
	void raster(vector<triangle>, rastert);

	void settexture(const GLubyte*, const int, const int, const int);
private:
	const int swidth;
	const int shight;
	const GLubyte* texture;
	int texwidth;
	int texhigh;
	int linebyte;

	void linerast(vector<triangle>);
	void outputlinefrag(pixe, pixe, bool);
	void fillrast(vector<triangle>);
	void scanline(pixe*);
	void texscanline(pixe*);
	void texrast(vector<triangle>);
	int round(float);
};
