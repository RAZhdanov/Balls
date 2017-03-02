#include "stdafx.h"
#include "Brush.h"
#include "FilledCircle.h"


Brush::Brush(HDC &hdc, const FilledCircle *p) :_hdc(hdc)
{
	LOGBRUSH lb = { p->_fill_style, p->_fill_c, p->_hatch_style }; 
	HBRUSH hNewBrush = CreateBrushIndirect(&lb);
	_hBrush = (HBRUSH)SelectObject(hdc, hNewBrush);
}


Brush::~Brush()
{
	DeleteObject(SelectObject(_hdc, _hBrush));
}
