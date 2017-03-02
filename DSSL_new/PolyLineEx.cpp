#include "StdAfx.h"
#include "PolyLineEx.h"


PolyLineEx::PolyLineEx(const POINT* lpPoints, int number_of_elements, const Color &line_color, int line_width, int line_style)
	:lpPoints_(lpPoints), number_of_elements_(number_of_elements), OutlinedCircle(line_color, line_width, line_style)
{
}


PolyLineEx::~PolyLineEx(void)
{
}

void PolyLineEx::Draw(HDC& hdc)const
{
	::Polyline(hdc, lpPoints_, number_of_elements_);
}