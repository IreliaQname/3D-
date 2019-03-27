#include <iostream>
#include <glut/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "camera.h"
#include "vector3.h"
#include "vector.h"
#include "matrix4.h"
#include "light.h"
#include "triangle.h"
#include "clip.h"
#include "vld.h"
#include "Getxy.h"
#include "vector4.h"
#include "drogn.h"
#include <assert.h>
#include <vld.h>

#define COL 800
#define ROW 800
using namespace std;

float array0[ROW][COL][3];


const vec3 arr[] = { vec3(-0.5,-0.5,-0.5),vec3(0,0,-1),vec3(1,0.5,0.2),vec3(0,0,0),
vec3(0.5,-0.5,-0.5),vec3(0,0,-1),vec3(1,0.5,0.2),vec3(1,0,0),
vec3(0,0,-0.5),vec3(0,0,-1),vec3(1,0.5,0.2),vec3(0.5,0.5,0),

vec3(0,0,-0.5),vec3(0,0,-1),vec3(1,0.5,0.2),vec3(0.5,0.5,0),
vec3(0.5,-0.5,-0.5),vec3(0,0,-1),vec3(1,0.5,0.2),vec3(1,0,0),
vec3(0.5,0.5,-0.5),vec3(0,0,-1),vec3(1,0.5,0.2),vec3(1,1,0),

vec3(0,0,-0.5),vec3(0,0,-1),vec3(1,0.5,0.2),vec3(0.5,0.5,0),
vec3(0.5,0.5,-0.5),vec3(0,0,-1),vec3(1,0.5,0.2),vec3(1,1,0),
vec3(-0.5,0.5,-0.5),vec3(0,0,-1),vec3(1,0.5,0.2),vec3(0,1,0),

vec3(0,0,-0.5),vec3(0,0,-1),vec3(1,0.5,0.2),vec3(0.5,0.5,0),
vec3(-0.5,0.5,-0.5),vec3(0,0,-1),vec3(1,0.5,0.2),vec3(0,1,0),
vec3(-0.5,-0.5,-0.5),vec3(0,0,-1),vec3(1,0.5,0.2),vec3(0,0,0),//4

vec3(-0.5,-0.5,0.5),vec3(0,0,1),vec3(1,0.5,0.2),vec3(0,0,0),
vec3(0.5,-0.5,0.5),vec3(0,0,1),vec3(1,0.5,0.2),vec3(1,0,0),
vec3(0,0,0.5),vec3(0,0,1),vec3(1,0.5,0.2),vec3(0.5,0.5,0),

vec3(0.5,0.5,0.5),vec3(0,0,1),vec3(1,0.5,0.2),vec3(1,1,0),
vec3(0.5,-0.5,0.5),vec3(0,0,1),vec3(1,0.5,0.2),vec3(1,0,0),
vec3(0,0,0.5),vec3(0,0,1),vec3(1,0.5,0.2),vec3(0.5,0.5,0),

vec3(0.5,0.5,0.5),vec3(0,0,1),vec3(1,0.5,0.2),vec3(1,1,0),
vec3(-0.5,0.5,0.5),vec3(0,0,1),vec3(1,0.5,0.2),vec3(0,1,0),
vec3(0,0,0.5),vec3(0,0,1),vec3(1,0.5,0.2),vec3(0.5,0.5,0),

vec3(-0.5,-0.5,0.5),vec3(0,0,1),vec3(1,0.5,0.2),vec3(0,0,0),
vec3(-0.5,0.5,0.5),vec3(0,0,1),vec3(1,0.5,0.2),vec3(0,1,0),
vec3(0,0,0.5),vec3(0,0,1),vec3(1,0.5,0.2),vec3(0.5,0.5,0),//8

vec3(-0.5,0.5,0.5),vec3(-1,0,0),vec3(1,0.5,0.2),vec3(1,1,0),
vec3(-0.5,0.5,-0.5),vec3(-1,0,0),vec3(1,0.5,0.2),vec3(0,1,0),
vec3(-0.5,0,0),vec3(-1,0,0),vec3(1,0.5,0.2),vec3(0.5,0.5,0),

vec3(-0.5,-0.5,-0.5),vec3(-1,0,0),vec3(1,0.5,0.2),vec3(0,0,0),
vec3(-0.5,0.5,-0.5),vec3(-1,0,0),vec3(1,0.5,0.2),vec3(0,1,0),
vec3(-0.5,0,0),vec3(-1,0,0),vec3(1,0.5,0.2),vec3(0.5,0.5,0),

vec3(-0.5,-0.5,-0.5),vec3(-1,0,0),vec3(1,0.5,0.2),vec3(0,0,0),
vec3(-0.5,-0.5,0.5),vec3(-1,0,0),vec3(1,0.5,0.2),vec3(1,0,0),
vec3(-0.5,0,0),vec3(-1,0,0),vec3(1,0.5,0.2),vec3(0.5,0.5,0),

vec3(-0.5,0.5,0.5),vec3(-1,0,0),vec3(1,0.5,0.2),vec3(1,1,0),
vec3(-0.5,-0.5,0.5),vec3(-1,0,0),vec3(1,0.5,0.2),vec3(1,0,0),
vec3(-0.5,0,0),vec3(-1,0,0),vec3(1,0.5,0.2),vec3(0.5,0.5,0),//12

vec3(0.5,0.5,0.5),vec3(1,0,0),vec3(1,0.5,0.2),vec3(0,1,0),
vec3(0.5,0.5,-0.5),vec3(1,0,0),vec3(1,0.5,0.2),vec3(1,1,0),
vec3(0.5,0,0),vec3(1,0,0),vec3(1,0.5,0.2),vec3(0.5,0.5,0),

vec3(0.5,-0.5,-0.5),vec3(1,0,0),vec3(1,0.5,0.2),vec3(1,0,0),
vec3(0.5,0.5,-0.5),vec3(1,0,0),vec3(1,0.5,0.2),vec3(1,1,0),
vec3(0.5,0,0),vec3(1,0,0),vec3(1,0.5,0.2),vec3(0.5,0.5,0),

vec3(0.5,-0.5,-0.5),vec3(1,0,0),vec3(1,0.5,0.2),vec3(1,0,0),
vec3(0.5,-0.5,0.5),vec3(1,0,0),vec3(1,0.5,0.2),vec3(0,0,0),
vec3(0.5,0,0),vec3(1,0,0),vec3(1,0.5,0.2),vec3(0.5,0.5,0),

vec3(0.5,0.5,0.5),vec3(1,0,0),vec3(1,0.5,0.2),vec3(0,1,0),
vec3(0.5,-0.5,0.5),vec3(1,0,0),vec3(1,0.5,0.2),vec3(0,0,0),
vec3(0.5,0,0),vec3(1,0,0),vec3(1,0.5,0.2),vec3(0.5,0.5,0),//16

vec3(-0.5,0.5,-0.5),vec3(0,1,0),vec3(1,0.5,0.2),vec3(0,1,0),
vec3(0.5,0.5,-0.5),vec3(0,1,0),vec3(1,0.5,0.2),vec3(1,1,0),
vec3(0,0.5,0),vec3(0,1,0),vec3(1,0.5,0.2),vec3(0.5,0.5,0),

vec3(0.5,0.5,0.5),vec3(0,1,0),vec3(1,0.5,0.2),vec3(1,0,0),
vec3(0.5,0.5,-0.5),vec3(0,1,0),vec3(1,0.5,0.2),vec3(1,1,0),
vec3(0,0.5,0),vec3(0,1,0),vec3(1,0.5,0.2),vec3(0.5,0.5,0),

vec3(0.5,0.5,0.5),vec3(0,1,0),vec3(1,0.5,0.2),vec3(1,0,0),
vec3(-0.5,0.5,-0.5),vec3(0,1,0),vec3(1,0.5,0.2),vec3(0,0,0),
vec3(0,0.5,0),vec3(0,1,0),vec3(1,0.5,0.2),vec3(0.5,0.5,0),

vec3(-0.5,0.5,-0.5),vec3(0,1,0),vec3(1,0.5,0.2),vec3(0,1,0),
vec3(-0.5,0.5,0.5),vec3(0,1,0),vec3(1,0.5,0.2),vec3(0,0,0),
vec3(0,0.5,0),vec3(0,1,0),vec3(1,0.5,0.2),vec3(0.5,0.5,0),//20

vec3(-0.5,-0.5,-0.5),vec3(0,-1,0),vec3(1,0.5,0.2),vec3(0,1,0),
vec3(0.5,-0.5,-0.5),vec3(0,-1,0),vec3(1,0.5,0.2),vec3(1,1,0),
vec3(0,-0.5,0),vec3(0,-1,0),vec3(1,0.5,0.2),vec3(0.5,0.5,0),

vec3(0.5,-0.5,0.5),vec3(0,-1,0),vec3(1,0.5,0.2),vec3(1,0,0),
vec3(0.5,-0.5,-0.5),vec3(0,-1,0),vec3(1,0.5,0.2),vec3(1,1,0),
vec3(0,-0.5,0),vec3(0,-1,0),vec3(1,0.5,0.2),vec3(0.5,0.5,0),

vec3(0.5,-0.5,0.5),vec3(0,-1,0),vec3(1,0.5,0.2),vec3(1,0,0),
vec3(-0.5,-0.5,0.5),vec3(0,-1,0),vec3(1,0.5,0.2),vec3(0,0,0),
vec3(0,-0.5,0),vec3(0,-1,0),vec3(1,0.5,0.2),vec3(0.5,0.5,0),

vec3(-0.5,-0.5,-0.5),vec3(0,-1,0),vec3(1,0.5,0.2),vec3(0,1,0),
vec3(-0.5,-0.5,0.5),vec3(0,-1,0),vec3(1,0.5,0.2),vec3(0,0,0),
vec3(0,-0.5,0),vec3(0,-1,0),vec3(1,0.5,0.2),vec3(0.5,0.5,0),//24


};

vec3 campos(2, 2, 2);
vec3 camtarg(0, 0, 0);
vec3 worup(0, 1, 0);
camera ca(campos, camtarg, worup);
int restmode = 0;
int i = restmode;
vec3 lightpos(2, 2, 2);
camera lt(lightpos,camtarg,worup);
void Keys(int key, int x, int y)
{
	
	if (key == GLUT_KEY_LEFT)
	{
		ca.mov(RIGHT);
		lt.mov(RIGHT);
	}
		
	if (key == GLUT_KEY_RIGHT)
	{
		ca.mov(LEFT);
		lt.mov(LEFT);
	}
		
	if (key == GLUT_KEY_F1)
	{		
		restmode = i % 3;
		i++;
	}
	glutPostRedisplay();
}


GLubyte* loadtex(const char* filename, int &texwidth, int &texhigh, int &linebyte)
{
	int width, height, total;
	GLubyte* pix;
	FILE* pfile;
	fopen_s(&pfile, filename, "rb");
	if (pfile == 0)
		return 0;
	fseek(pfile, 0x0012, 0);
	fread(&width, 4, 1, pfile);
	fread(&height, 4, 1, pfile);
	fseek(pfile, 54, 0);
	texhigh = height;
	texwidth = width;

	int linebys = width * 4;

	while (linebys % 4 != 0)
	{
		linebys++;
	}
	linebyte = linebys;
	total = linebys *height;

	pix = (GLubyte*)malloc(total);

	if (pix == 0)
	{
		fclose(pfile);
		return 0;
	}
	if (fread(pix, total, 1, pfile) <= 0)
	{
		free(pix);
		fclose(pfile);
		return 0;
	}
	return pix;

}

//图片
int texwid, texheih, linebyt;
const GLubyte *texture = loadtex("w.bmp", texwid, texheih, linebyt);

void Print()
{
	glClear(GL_COLOR_BUFFER_BIT);
	matrix4 mode0 ;
	mode0 = matrix4::tra(mode0, vec3(0, 0, 0));	
	matrix4 view0= ca.Lookat();
	matrix4 project0 = matrix4::project(-0.5, 0.5, 0.5, -0.5, 0.8, 500);
	light light(lightpos, vec3(1, 1, 1), vec3(1, 1, 1),0.1, 0.1, ca.campos);
	getxy getxy(arr,sizeof(arr) / sizeof(vec3));
	getxy.colorver(light, mode0, restmode);
	getxy.transform(mode0, view0,project0);
	clip clip(getxy.buff);
	clip.clipall();
	drogn rast(COL, ROW);
	rast.settexture(texture, texwid, texheih, linebyt);
	glutSpecialFunc(Keys);
	switch (restmode)
	{
	case 0:
		rast.raster(clip.cli, LINE);
		break;
	case 1:
		rast.raster(clip.cli, FILL);
		break;
	case 2:
		rast.raster(clip.cli, TEXTURE);
		break;
	}
	
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			array0[i][j][0] = rast.framebuff[i][j].color.x;
			array0[i][j][1] = rast.framebuff[i][j].color.y;
			array0[i][j][2] = rast.framebuff[i][j].color.z;
		}
	}

	glDrawPixels(COL, ROW, GL_RGB, GL_FLOAT, array0);
	glutSwapBuffers();
	glutPostRedisplay();
}

int main()
{
	cout << endl;
	cout << "***方向键改变观察角度***" << endl;
	cout << "***F1改变物体模式***" << endl;
	glutInitDisplayMode( GLUT_DOUBLE |GLUT_RGB );
	glutInitWindowPosition(800, 300);
	glutInitWindowSize(COL, ROW);
	glutCreateWindow("刘佳伟");
	glClearColor(0, 0, 0, 0);
	glutDisplayFunc(Print);
	glutMainLoop();
	return 0;
}


