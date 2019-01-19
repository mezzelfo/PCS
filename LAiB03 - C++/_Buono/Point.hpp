#ifndef POINT_INC
#define POINT_INC
#include <iostream>
#include <math.h>
class Point
{
	double x, y;
public:
	Point() {std::cout<<"Creato un punto vuoto"<<std::endl;}
	~Point() {}

	Point(double, double);
	Point(const Point&);
	
	double getX() const {return x;};
	double getY() const {return y;};
	double getNorm() const {return sqrt(x*x+y*y);};
	

	friend std::ostream& operator<<(std::ostream& str, Point& P) {str<<"("<<P.x<<", "<<P.y<<")"; return str;};
	friend Point operator+(const Point& lhs, const Point& rhs);
	friend Point operator-(const Point& lhs, const Point& rhs);
	friend bool operator==(const Point& lhs, const Point& rhs);

	static const double tol;
	bool operator<(const Point& P) const
	{
		//std::cout<<"Confronto i punti "<<x<<","<<y<<" e "<<P.x<<","<<P.y<<std::endl;
		double n1 = getNorm();
		double n2 = P.getNorm();
		if (abs(n1-n2) <= tol)
		{
			if (abs(x-P.x) <= tol) return (y < P.y); else return (x < P.x);
		}
		else return (n1 < n2);
	}
};

#endif
