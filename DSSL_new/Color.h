#pragma once
class Color
{
public:
	operator COLORREF()const;
	Color(unsigned char red = 0, unsigned char green = 0, unsigned char blue = 0);
	virtual ~Color();
private:
	unsigned char _r, _g, _b;
};

