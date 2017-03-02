#pragma once
#include "FilledCircle.h"
#include "Color.h"

//Замкнутый многоугольник
class PolygonEx :
	public FilledCircle
{
public:
	virtual void Draw(HDC &hdc)const;
	PolygonEx(const POINT* lpPoints, int number_of_elements, int fill_style, const Color &fill_color, int hatch_style, const Color &line_color, int line_width, int line_style);
	virtual ~PolygonEx(void);
private:
	const POINT* lpPoints_;
	const int number_of_elements_;
};

