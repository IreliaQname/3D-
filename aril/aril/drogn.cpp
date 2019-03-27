#include "drogn.h"
#include "pix.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;
drogn::drogn(int screwith, int screhigh) :shight(screhigh), swidth(screwith)
{
	framebuff = new pixe*[shight];
	for (int i = 0; i < shight; i++)
	{
		framebuff[i] = new pixe[swidth];
	}
	texture = NULL;
	texwidth = -1;
	texhigh = -1;
	linebyte = -1;
}

void drogn::raster(vector<triangle> vec, rastert type)
{
	switch (type)
	{
	case rastert::LINE:
		linerast(vec);
		break;
	case rastert::FILL:
		fillrast(vec);
		break;
	case rastert::TEXTURE:
		texrast(vec);


	}
}

void drogn::settexture(const GLubyte* texture0, const int texwith, const int texhigh0,const int linebyte0)
{
	texture = texture0;
	texwidth = texwith;
	texhigh = texhigh0;
	linebyte = linebyte0;

}

void drogn::linerast(vector<triangle> vec)
{
	for (vector<triangle>::iterator it = vec.begin(); it != vec.end(); it++)
	{
		fragment frag;
		for (int i = 0; i < 3; i++)
		{
			pixe p1;
			p1.pixlx = round(swidth*(it->vert[i].pos.x + 1) / 2);
			p1.pixly = round(swidth*(it->vert[i].pos.y + 1) / 2);
			p1.depth = it->vert[i].pos.z;
			p1.color = it->vert[i].color;
			pixe p2;
			p2.pixlx = round(swidth*(it->vert[(i + 1) % 3].pos.x + 1) / 2);
			p2.pixly = round(swidth*(it->vert[(i + 1) % 3].pos.y + 1) / 2);
			p2.depth = it->vert[(i + 1) % 3].pos.z;
			p2.color = it->vert[(i + 1) % 3].color;

			frag.pixes.push_back(p1);
			frag.pixes.push_back(p2);

			if (p1.pixlx < p2.pixlx)
			{
				outputlinefrag(p1, p2, true);
			}
			else if (p1.pixlx > p2.pixlx)
			{
				outputlinefrag(p2, p1, true);
			}
			else
				outputlinefrag(p1, p2, false);
		}
	}
}

void drogn::outputlinefrag(pixe a, pixe b, bool islop)
{
	float k = 0;
	float zk = 0;
	float colorx = 0;
	float colory = 0;
	float colorz = 0;
	bool isxdir = true;
	if (islop)
	{
		k = (float)(a.pixly - b.pixly) / (a.pixlx - b.pixlx);
		zk= (float)(a.depth - b.depth) / (a.pixlx - b.pixlx);
		colorx = (a.color.x - b.color.x) / (a.pixlx - b.pixlx);
		colory = (a.color.y - b.color.y) / (a.pixlx - b.pixlx);
		colorz = (a.color.z - b.color.z) / (a.pixlx - b.pixlx);
	}
	if (abs(k) > 1 || !islop)
	{
		k = (float)(a.pixlx - b.pixlx) / (a.pixly - b.pixly);
		zk = (float)(a.depth - b.depth) / (a.pixly - b.pixly);
		colorx = (a.color.x - b.color.x) / (a.pixly - b.pixly);
		colory = (a.color.y - b.color.y) / (a.pixly - b.pixly);
		colorz = (a.color.z - b.color.z) / (a.pixly - b.pixly);
		isxdir = false;
	}
	if (isxdir)
	{
		float y = (float)a.pixly;
		float z = (float)a.depth;
		float tmpcolorx = a.color.x;
		float tmpcolory = a.color.y;
		float tmpcolorz = a.color.z;
		for (int i = a.pixlx; i <= b.pixlx; i++)
		{
			y += k;
			z += zk;
			pixe p;
			p.pixlx = i;
			p.pixly = round(y);
			p.depth = z;
			tmpcolorx += colorx;
			tmpcolory += colory;
			tmpcolorz += colorz;
			p.color = vec3(tmpcolorx, tmpcolory, tmpcolorz);
			if (p.pixlx >= swidth)p.pixlx = swidth - 1;
			if (p.pixly >= shight)p.pixly = shight - 1;
			if (p.depth > framebuff[p.pixly][p.pixlx].depth)
				framebuff[p.pixly][p.pixlx] = p;
		}
	}
	else
	{
		float x;
		float z;
		int j, h;
		float tmpcolorx;
		float tmpcolory;
		float tmpcolorz;
		if (a.pixly < b.pixly)
		{
			j = a.pixly;
			h = b.pixly;
			x = (float)a.pixlx;
			z = (float)a.depth;
			tmpcolorx = a.color.x;
			tmpcolory = a.color.y;
			tmpcolorz = a.color.z;

		}
		else
		{
			j = b.pixly;
			h = a.pixly;
			x = (float)b.pixlx;
			z = (float)b.depth;
			tmpcolorx = b.color.x;
			tmpcolory = b.color.y;
			tmpcolorz = b.color.z;

		}
		for (int i = j + 1; i < h; i++)
		{
			x += k;
			z += zk;
			pixe p;
			p.pixly = i;
			p.pixlx = round(x);
			p.depth = z;
			tmpcolorx += colorx;
			tmpcolory += colory;
			tmpcolorz += colorz;
			p.color = vec3(tmpcolorx, tmpcolory, tmpcolorz);
			if (p.pixlx >= swidth)p.pixlx = swidth - 1;
			if (p.pixly >= shight)p.pixly = shight - 1;
			if (p.depth > framebuff[p.pixly][p.pixlx].depth)
				framebuff[p.pixly][p.pixlx] = p;
		}
	}
}

void drogn::fillrast(vector<triangle> vec)
{
	for (vector<triangle>::iterator it = vec.begin(); it != vec.end(); it++)
	{
		it->mysort();
		pixe p[3];
		for (int i = 0; i < 3; i++)
		{
			p[i].pixlx = round(swidth*(it->vert[i].pos.x + 1) / 2);
			p[i].pixly = round(shight*(it->vert[i].pos.y + 1) / 2);
			p[i].depth = it->vert[i].pos.z;
			p[i].color = it->vert[i].color;
		}
		scanline(p);
	}
}

void drogn::scanline(pixe* p)
{
	fragment frag;
	edge **et = new edge*[shight];
	edge*aet;

	for (int i = 0; i < shight; i++)
	{
		et[i] = new edge();
	}
	aet = new edge();
	aet->next = NULL;

	for (int i = 0; i < 3; i++)
	{
		int x0 = p[(i + 2) % 3].pixlx;
		int y0 = p[(i + 2) % 3].pixly;
		int x1 = p[i].pixlx;
		int y1 = p[i].pixly;
		int x2 = p[(i + 1) % 3].pixlx;
		int y2 = p[(i + 1) % 3].pixly;

		if (y1 == y2)
		{
			continue;
		}
		int ymin = y1 > y2 ? y2 : y1;
		int ymax = y1 > y2 ? y1 : y2;
		float x = y1 > y2 ? x2 : x1;
		float dx = (float)(x1 - x2)/ (y1 - y2);

		float dcolorx = (p[i].color.x - p[(i + 1) % 3].color.x) / (y1 - y2);
		float dcolory = (p[i].color.y - p[(i + 1) % 3].color.y) / (y1 - y2);
		float dcolorz = (p[i].color.x - p[(i + 1) % 3].color.z) / (y1 - y2);

		vec3 color = y1 > y2 ? p[(i + 1) % 3].color : p[i].color;
		float dz= (p[i].depth - p[(i + 1) % 3].depth) / (y1 - y2);
		float z = y1 > y2 ? p[(i + 1) % 3].depth : p[i].depth;

		if (((y2 < y1) && (y2 > y0))|| (y1 < y2) && (y1 > y0))
		{
			ymin++;
			x += dx;
			color.x += dcolorx;
			color.y += dcolory;
			color.z += dcolorz;
			z += dz;

		}
		edge *pi = new edge();
		pi->x = x;
		pi->dx = dx;
		pi->ymax = ymax;
		pi->color = color;
		pi->dcolorx = dcolorx;
		pi->dcolory = dcolory;
		pi->dcolorz = dcolorz;
		pi->depth = z;
		pi->dz = dz;
		pi->next = et[ymin]->next;
		et[ymin]->next = pi;
	}

	for (int i = 0; i < shight; i++)
	{
		while (et[i]->next)
		{
			edge* pinsert = et[i]->next;
			edge* pi = aet;

			while (pi->next)
			{
				if (pinsert->x >pi->next->x)
				{
					pi = pi->next;
					continue;
				}
				if (pinsert->x == pi->next->x&&pinsert->dx > pi->next->dx)
				{
					pi = pi->next;
					continue;
				}
				break;
			}
			et[i]->next = pinsert->next;
			pinsert->next =pi->next;
			pi->next = pinsert;
		}
		edge *pi = aet;
		if (pi->next&&pi->next->next)
		{
			float dcolorx = (pi->next->color.x - pi->next->next->color.x) / (pi->next->x - pi->next->next->x);
			float dcolory = (pi->next->color.y - pi->next->next->color.y) / (pi->next->x - pi->next->next->x);
			float dcolorz = (pi->next->color.z - pi->next->next->color.z) / (pi->next->x - pi->next->next->x);
			float dz = (pi->next->depth - pi->next->next->depth) / (pi->next->x - pi->next->next->x);
			vec3 tmpcolor = pi->next->color;
			float z = pi->next->depth;
			for (int x = round(pi->next->x); x < round(pi->next->next->x); x++)
			{
				pixe pix;
				pix.pixlx = x;
				pix.pixly = i;
				pix.color = tmpcolor;
				pix.depth = z;

				if (pix.pixlx >= swidth)pix.pixlx = swidth - 1;
				if (pix.pixly >= shight)pix.pixly = shight - 1;
				if (pix.depth > framebuff[pix.pixly][pix.pixlx].depth)
					framebuff[pix.pixly][pix.pixlx] = pix;

				tmpcolor.x += dcolorx;
				tmpcolor.y += dcolory;
				tmpcolor.z += dcolorz;
				z += dz;

			}
		}
		pi = aet;
		while (pi->next)
		{
			if (pi->next->ymax == i)
			{
				edge *pdelete = pi->next;
				pi->next = pdelete->next;
				pdelete->next = NULL;
				delete pdelete;
			}
			else
			{
				pi = pi->next;
			}
		}
		pi = aet;
		while (pi->next)
		{
			pi->next->x += pi->next->dx;
			pi->next->depth += pi->next->dz;
			pi->next->color.x += pi->next->dcolorx;
			pi->next->color.y += pi->next->dcolory;
			pi->next->color.z += pi->next->dcolorz;
			pi = pi->next;
		}
	}
	for (int i = 0; i < shight; i++)
	{
		delete et[i];
	}
	delete[]et;
	delete aet;

}
void drogn::texrast(vector<triangle> vec)
{
	if (texture == NULL)
		return;
	for (vector<triangle>::iterator it = vec.begin(); it != vec.end(); it++)
	{
		it->mysort();
		pixe p[3];
		for (int i = 0; i < 3; i++)
		{
			p[i].pixlx = round(swidth*(it->vert[i].pos.x + 1) / 2);
			p[i].pixly = round(shight*(it->vert[i].pos.y + 1) / 2);
			p[i].depth = it->vert[i].pos.z;
			p[i].color = it->vert[i].color;
			p[i].u = it->vert[i].tex[0];
			p[i].v = it->vert[i].tex[1];

		}
		texscanline(p);
	}
}

void drogn::texscanline(pixe* pix)
{
	fragment frag;
	edge **et = new edge*[shight];
	edge* aet;
	for (int i = 0; i < shight; i++)
	{
		et[i] = new edge();
	}
	aet = new edge();
	aet->next = NULL;

	for (int i = 0; i < 3; i++)
	{
		int x0 = pix[(i + 2) % 3].pixlx;
		int y0 = pix[(i + 2) % 3].pixly;
		int x1 = pix[i].pixlx; 
		int y1 = pix[i].pixly;
		int x2 = pix[(i + 1) % 3].pixlx;
		int y2 = pix[(i + 1) % 3].pixly;


		if (y1 == y2)
		{
			continue;
		}
		int ymin = y1 > y2 ? y2 : y1;
		int ymax = y1 > y2 ? y1 : y2;
		float x = y1 > y2 ? x2 : x1;
		float dx = (float)(x1 - x2) / (y1 - y2);

		float dcolorx = (pix[i].color.x - pix[(i + 1) % 3].color.x) / (y1 - y2);
		float dcolory = (pix[i].color.y - pix[(i + 1) % 3].color.y) / (y1 - y2);
		float dcolorz = (pix[i].color.x - pix[(i + 1) % 3].color.z) / (y1 - y2);

		vec3 color = y1 > y2 ? pix[(i + 1) % 3].color : pix[i].color;
		float du= (pix[i].u - pix[(i + 1) % 3].u) / (y1 - y2);
		float dv = (pix[i].v - pix[(i + 1) % 3].v) / (y1 - y2);

		float u = y1 > y2 ? pix[(i + 1) % 3].u : pix[i].u;
		float v = y1 > y2 ? pix[(i + 1) % 3].v : pix[i].v;

		float dz = (pix[i].depth - pix[(i + 1) % 3].depth) / (y1 - y2);
		float z = y1 > y2 ? pix[(i + 1) % 3].depth : pix[i].depth;

		if (((y2 < y1) && (y2 > y0)) || (y1 < y2) && (y1 > y0))
		{
			ymin++;
			x += dx;
			color.x += dcolorx;
			color.y += dcolory;
			color.z += dcolorz;
			z += dz;
			u += du;
			v += dv;

		}
		edge *pi = new edge();
		pi->x = x;
		pi->dx = dx;
		pi->ymax = ymax;
		pi->tex[0] = u;
		pi->tex[1] = v;
		pi->color = color;
		pi->dcolorx = dcolorx;
		pi->dcolory = dcolory;
		pi->dcolorz = dcolorz;
		pi->depth = z;
		pi->dz = dz;
		pi->dU = du;
		pi->dV = dv;

		pi->next = et[ymin]->next;
		et[ymin]->next = pi;
	}

	for (int i = 0; i < shight; i++)
	{
		while (et[i]->next)
		{
			edge* pinsert = et[i]->next;
			edge* pi = aet;

			while (pi->next)
			{
				if (pinsert->x > pi->next->x)
				{
					pi = pi->next;
					continue;
				}
				if (pinsert->x == pi->next->x&&pinsert->dx > pi->next->dx)
				{
					pi = pi->next;
					continue;
				}
				break;
			}
			et[i]->next = pinsert->next;
			pinsert->next = pi->next;
			pi->next = pinsert;
		}
		edge *pi = aet;
		if (pi->next&&pi->next->next)
		{
			float dcolorx = (pi->next->color.x - pi->next->next->color.x) / (pi->next->x - pi->next->next->x);
			float dcolory = (pi->next->color.y - pi->next->next->color.y) / (pi->next->x - pi->next->next->x);
			float dcolorz = (pi->next->color.z - pi->next->next->color.z) / (pi->next->x - pi->next->next->x);
			float du= (pi->next->tex[0]- pi->next->next->tex[0])/ (pi->next->x - pi->next->next->x);
			float dv= (pi->next->tex[1] - pi->next->next->tex[1]) / (pi->next->x - pi->next->next->x);
			float dz = (pi->next->depth - pi->next->next->depth) / (pi->next->x - pi->next->next->x);

			float tmpu = pi->next->tex[0];
			float tmpv= pi->next->tex[1];

			vec3 tmpcolor = pi->next->color;
			float z = pi->next->depth;
			for (int x = round(pi->next->x); x < round(pi->next->next->x); x++)
			{
				pixe pix;
				pix.pixlx = x;
				pix.pixly = i;
				//pix.color = tmpcolor;
				pix.depth = z;
				pix.u = tmpu;
				pix.v = tmpv;
				int h= round(pix.v*(texwidth - 1));
				int zz = round(pix.v*(texhigh - 1));

				pix.color.x = (texture[zz*linebyte + h * 3 + 2] / 255.0)*tmpcolor.x;
				pix.color.y = (texture[zz*linebyte + h * 3 + 1] / 255.0)*tmpcolor.y;
				pix.color.z = (texture[zz*linebyte + h * 3 + 0] / 255.0)*tmpcolor.z;

				if (pix.pixlx >= swidth)pix.pixlx = swidth - 1;
				if (pix.pixly >= shight)pix.pixly = shight - 1;
				if (pix.depth > framebuff[pix.pixly][pix.pixlx].depth)
					framebuff[pix.pixly][pix.pixlx] = pix;

				tmpu += du;
				tmpv += dv;
				tmpcolor.x += dcolorx;
				tmpcolor.y += dcolory;
				tmpcolor.z += dcolorz;
				z += dz;

			}
		}
		pi = aet;
		while (pi->next)
		{
			if (pi->next->ymax == i)
			{
				edge *pdelete = pi->next;
				pi->next = pdelete->next;
				pdelete->next = NULL;
				delete pdelete;
			}
			else
			{
				pi = pi->next;
			}
		}
		pi = aet;
		while (pi->next)
		{
			pi->next->x += pi->next->dx;
			pi->next->depth += pi->next->dz;
			pi->next->tex[0] += pi->next->dU;
			pi->next->tex[1] += pi->next->dV;
			pi->next->color.x += pi->next->dcolorx;
			pi->next->color.y += pi->next->dcolory;
			pi->next->color.z += pi->next->dcolorz;
			pi = pi->next;
		}
	}

	for (int i = 0; i < shight; i++)
	{
		delete et[i];
	}
	delete[]et;
	delete aet;

	
}

int drogn::round(float _f)
{
	return (int)(_f + 0.5);
}