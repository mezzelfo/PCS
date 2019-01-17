#ifndef POINT_INC
#define POINT_INC
#include <iostream>
#include <math.h>
class Point
{
	double x, y;
public:
	Point();
	Point(double, double);
	~Point();
	Point(const Point&);
	double getX() const {return x;};
	double getY() const {return y;};
	double getNorm() const {return sqrt(x*x+y*y);};
	

	friend std::ostream& operator<<(std::ostream& str, Point& P) {str<<"("<<P.x<<", "<<P.y<<")"; return str;};
	friend bool operator==(const Point& lhs, const Point& rhs);
	friend Point operator+(const Point& lhs, const Point& rhs);
	friend Point operator-(const Point& lhs, const Point& rhs);
};

#endif
