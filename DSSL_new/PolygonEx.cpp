#include "StdAfx.h"
#include "PolygonEx.h"
#include "Pen.h"
#include "Brush.h"


PolygonEx::PolygonEx(const POINT* lpPoints, int number_of_elements, int fill_style,	const Color &fill_color, int hatch_style, const Color &line_color, int line_width, int line_style):FilledCircle(fill_style, fill_color, hatch_style, line_color, line_width, line_style), lpPoints_(lpPoints), number_of_elements_(number_of_elements)
{
}


PolygonEx::~PolygonEx(void)
{
}

void PolygonEx::Draw(HDC &hdc)const
{
	Pen pen(hdc, this);
	Brush brush(hdc, this);

	::Polygon(hdc, lpPoints_, number_of_elements_);
}