#include "Point.hpp"

Point::Point()
{
	x = 0;
	y = 0;
	std::cout<<"Creato un punto vuoto"<<std::endl;
}

Point::Point(double xx, double yy)
{
	x = xx;
	y = yy;
	std::cout<<"Creato un punto ("<<x<<","<<y<<")"<<std::endl;
}

Point::~Point()
{

}

Point::Point(const Point& other)
{
	x = other.x;
	y = other.y;
	std::cout<<"Copiato un punto ("<<x<<","<<y<<")"<<std::endl;
}

bool operator==(const Point& lhs, const Point& rhs)
{
	if(lhs.x != rhs.x) return false;
	if(lhs.y != rhs.y) return false;
	return true;
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
