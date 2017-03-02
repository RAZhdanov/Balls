#include "stdafx.h"
#include "Point.h"

Point::Point(void)
{}
Point::Point(double x, double y) :_x(x), _y(y)
{}


Point::~Point()
{}

void Point::Set_X(const double &x)
{
	_x = x; 
}

void Point::Set_Y(const double &y)
{ 
	_y = y; 
}

double Point::Get_X(void)const
{
	return _x;
}

double Point::Get_Y(void)const
{ 
	return _y; 
}
