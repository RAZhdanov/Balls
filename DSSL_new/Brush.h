#pragma once
#include "FilledCircle.h"
class FilledCircle;
class Brush
{
public:
	Brush(HDC &hdc, const FilledCircle *p);
	virtual ~Brush();
private:
	HDC &_hdc;
	HBRUSH _hBrush;
};

