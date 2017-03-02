#pragma once

class OutlinedCircle;

class Pen
{
public:
	Pen(HDC &hdc, const OutlinedCircle *p);
	virtual ~Pen();
private:
	HDC &_hdc;
	HPEN _hPen;
};

