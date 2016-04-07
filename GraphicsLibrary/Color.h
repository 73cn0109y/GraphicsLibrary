#pragma once

class Color
{
public:
	Color() { }
	Color(int _r, int _g, int _b) { Color(_r, _g, _b, 255); }
	Color(int _r, int _g, int _b, int _a) { r = _r; g = _g; b = _b; a = _a; }

	int r;
	int g;
	int b;
	int a;
};