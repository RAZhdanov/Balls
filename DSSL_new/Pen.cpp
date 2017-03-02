#include "stdafx.h"
#include "Pen.h"
#include "OutlinedCircle.h"""


Pen::Pen(HDC &hdc, const OutlinedCircle *p) :_hdc(hdc), _hPen((HPEN)SelectObject(hdc, CreatePen(p->_style, p->_width, p->_c)))
{

}


Pen::~Pen()
{
	DeleteObject(SelectObject(_hdc, _hPen));
}
