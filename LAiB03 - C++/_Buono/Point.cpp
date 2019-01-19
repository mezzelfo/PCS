#include "Point.hpp"

const double Point::tol = 1e-10;

Point::Point(double xx, double yy)
{
	x = xx;
	y = yy;
	//std::cout<<"Creato un punto ("<<x<<","<<y<<")"<<std::endl;
}

Point::Point(const Point& other)
{
	x = other.x;
	y = other.y;
	//std::cout<<"Copiato un punto ("<<x<<","<<y<<")"<<std::endl;
}

Point operator+(const Point& lhs, const Point& rhs)
{
	double newx = lhs.x+rhs.x;
	double newy = lhs.y+rhs.y;
	return Point(newx, newy);
}

Point operator-(const Point& lhs, const Point& rhs)
{
	double newx = lhs.x-rhs.x;
	double newy = lhs.y-rhs.y;
	return Point(newx, newy);
}

bool operator==(const Point& lhs, const Point& rhs)
{
	if(abs(lhs.x - rhs.x) > Point::tol) return false;
	if(abs(lhs.y - rhs.y) > Point::tol) return false;
	return true;
}
