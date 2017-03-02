#pragma once
#include "Color.h"
class OutlinedCircle
{
public:
	friend class Pen;
	OutlinedCircle(const Color &color = Color(), int width = 1, int style = PS_SOLID) :_style(style), _width(width), _c(color)
	{
	}

	virtual ~OutlinedCircle()
	{
	}
private:
	int _style;
	int _width;
	Color _c;
};

