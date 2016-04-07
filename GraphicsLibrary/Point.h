#pragma once

class Point
{
public:
	Point() { Point(0.0, 0.0); }
	Point(float _x, float _y) { x = _x; y = _y; }

	float x;
	float y;
};