#ifndef EDGE_INC
#define EDGE_INC

#include <vector>
#include <math.h>
#include "Point.hpp"

class Edge
{
	int index1, index2;
	static std::vector<Point> vPoint;
public:
	Edge() {index1 = index2 = -1;}
	~Edge() {index1 = index2 = -1;}
	Edge(const Edge&);
	Edge(Point& P1, Point& P2);

	Point getA() const {return vPoint.at(index1);}
	Point getB() const {return vPoint.at(index2);}
	int getI1() const {return index1;}
	int getI2() const {return index2;}
	static Point getP(int i) {return vPoint.at(i);}

	double getLength();

	friend bool operator==(const Edge& lhs, const Edge& rhs);

};

#endif
