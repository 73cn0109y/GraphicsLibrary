#pragma once
#include "Color.h"
#include "Point.h"
#include <GL/glew.h>
#include "UV.h"

struct Vertex {
	Point location;
	Color color;
	UV uv;

	void setPosition(float x, float y)
	{
		location.x = x;
		location.y = y;
	}

	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
	{
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}

	void setUV(float u, float v)
	{
		uv.u = u;
		uv.v = v;
	}
};
