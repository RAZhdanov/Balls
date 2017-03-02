#include "stdafx.h"
#include "Color.h"


Color::Color(unsigned char red, unsigned char green, unsigned char blue) :_r(red), _g(green), _b(blue)
{
}


Color::~Color()
{
}

Color::operator COLORREF()const
{
	return RGB(_r, _g, _b);
}
