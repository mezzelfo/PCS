#ifndef EDGE_INC
#define EDGE_INC

#include <set>
#include <math.h>
#include "Point.hpp"

typedef std::set<Point>::iterator IteratorToPoint;

class Edge
{
	static std::set<Point> PointSet;
	IteratorToPoint index1, index2;
public:
	Edge() {std::cout<<"Creato un Edge vuoto"<<std::endl;}
	~Edge() {}
	Edge(const Edge& o);
	Edge(Point& P1, Point& P2);

	Point getA() const {return *index1;}
	Point getB() const {return *index2;}
	IteratorToPoint getPtrToA() const {return index1;}
	IteratorToPoint getPtrToB() const {return index2;}

	double getLength() const;

	friend bool operator==(const Edge& lhs, const Edge& rhs);
	bool operator<(const Edge& E) const
	{
		if (index1 == E.index1)
		{
			return (*index2 < *(E.index2));
		} else return (*index1 < *(E.index1));
	}

	static void printMem() {std::cout<<"Memorizzati "<<PointSet.size()<<" Point"<<std::endl;}

};

#endif
