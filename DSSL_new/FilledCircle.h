#pragma once
#include "OutlinedCircle.h"
class FilledCircle : public OutlinedCircle
{
public:
	friend class Brush;
	FilledCircle(int fill_style = BS_NULL,  const Color &fill_color = Color(255,255,255), int hatch_style = HS_HORIZONTAL, 
		int line_style = PS_SOLID, const Color &line_color = Color(), int width = 1) : _fill_style(fill_style), _fill_c(fill_color), _hatch_style(hatch_style),
		OutlinedCircle(line_color, width, line_style)
	{
	}

	virtual ~FilledCircle()
	{
	}
private:
	int _fill_style;
	Color _fill_c;
	int _hatch_style;

};

