#pragma once
#include "OutlinedCircle.h"
class PolyLineEx :
	public OutlinedCircle
{
public:
	PolyLineEx(const POINT* lpPoints, int number_of_elements, const Color &line_color = Color(), int line_width = 1, int line_style = PS_SOLID);
	virtual void Draw(HDC&)const;
	virtual ~PolyLineEx(void);
private:
	const POINT* lpPoints_;
	const int number_of_elements_;
};

