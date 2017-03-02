#pragma once
#include "Point.h"
#include "FilledCircle.h"
#include "Color.h"
class Circle : public FilledCircle
{
public:
	//Circle(void);
	Circle(const Point&, const double& radius, int fill_style = BS_NULL, const Color& fill_color = Color(255,255,255), int hatch_style = HS_HORIZONTAL, const Color& line_color = Color(), int width = 1, int line_style = PS_SOLID);
			
	void Draw(HDC&)const;

	void SetPos_X(const double &);
	double GetPos_X(void)const;

	void SetPos_Y(const double&);
	double GetPos_Y(void)const;

	void Set_Mass(const double&);
	double Get_Mass(void)const;

	void Set_Vx(const double&);
	double Get_Vx(void)const;

	void Set_Vy(const double&);
	double Get_Vy(void)const;

	void Set_Ax(const double&);
	double Get_Ax(void)const;

	void Set_Ay(const double&);
	double Get_Ay(void)const;

	void Set_dX(const double&);
	int Get_dX(void)const;

	void Set_dY(const double&);
	int Get_dY(void)const;

	void Set_radius(const double&);
	int Get_radius(void)const;
	virtual ~Circle();
private:
	Point _p;
	double _radius;
	double _mass;
	double _vx, _vy;
	double _ax, _ay;
};

