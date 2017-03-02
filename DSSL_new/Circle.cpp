#include "stdafx.h"
#include "Circle.h"
#include "Pen.h"
#include "Brush.h"
#include "Color.h"
Circle::Circle(const Point &p, const double &radius, int fill_style, const Color& fill_color, int hatch_style, const Color& line_color, int width, int line_style) :FilledCircle(fill_style, fill_color, hatch_style, line_style, line_color, width), _p(p), _radius(radius), _vx(0), _vy(0), _ax(0), _ay(0)
{
	this->_mass = radius;
}


Circle::~Circle()
{}

void Circle::Draw(HDC &hdc)const
{
	Pen pen(hdc, this);
	Brush brush(hdc, this);
	Ellipse(hdc, _p.Get_X() - _radius, _p.Get_Y() - _radius, _p.Get_X() + _radius, _p.Get_Y() + _radius);
}

void Circle::SetPos_X(const double &x)
{
	this->_p.Set_X(x);
}
double Circle::GetPos_X(void)const
{
	return _p.Get_X();
}

void Circle::SetPos_Y(const double &y)
{
	this->_p.Set_Y(y);
}
double Circle::GetPos_Y(void)const
{
	return _p.Get_Y();
}

void Circle::Set_Mass(const double &mass)
{
	this->_mass = mass;
}
double Circle::Get_Mass(void)const
{
	return _mass;
}

void Circle::Set_Vx(const double &vx)
{
	this->_vx = vx;
}
double Circle::Get_Vx(void)const
{
	return _vx;
}
void Circle::Set_Vy(const double &vy)
{
	this->_vy = vy;
}
double Circle::Get_Vy(void)const
{
	return _vy;
}

void Circle::Set_Ax(const double &ax)
{
	this->_ax = ax;
}
double Circle::Get_Ax(void)const
{
	return _ax;
}
void Circle::Set_Ay(const double &ay)
{
	this->_ay = ay;
}
double Circle::Get_Ay(void)const
{
	return _ay;
}
void Circle::Set_radius(const double& radius)
{
	_radius = radius;
}
int Circle::Get_radius(void)const
{
	return _radius;
}