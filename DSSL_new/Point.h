#pragma once
class Point
{
public:
	Point(void);
	Point(double, double);
	void Set_X(const double &x);
	void Set_Y(const double &y);
	double Get_X(void)const;
	double Get_Y(void)const;

	virtual ~Point();
private:
	double _x, _y;
};

