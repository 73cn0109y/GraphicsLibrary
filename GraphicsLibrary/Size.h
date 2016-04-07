#pragma once

class Size
{
public:
	Size() : width(1.0), height(1.0) { Size(1.0, 1.0); }
	Size(float _width, float _height) { width = _width; height = _height; }

	float width;
	float height;
};