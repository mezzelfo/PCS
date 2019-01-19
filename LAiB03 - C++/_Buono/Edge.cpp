#include "Edge.hpp"

std::set<Point> Edge::PointSet;

Edge::Edge(Point& P1, Point& P2)
{
	index1 = PointSet.insert(P1).first;
	index2 = PointSet.insert(P2).first;
	//std::cout<<"Creato un Edge pieno"<<std::endl;
}

Edge::Edge(const Edge& o)
{
	index1 = o.index1;
	index2 = o.index2;
	//std::cout<<"Copiato un Edge"<<std::endl;
}

double Edge::getLength() const
{
	Point d = *index1 - *index2;
	return d.getNorm();
}

bool operator==(const Edge& lhs, const Edge& rhs)
{
	if ((lhs.index1 == rhs.index1) and (lhs.index2 == rhs.index2)) return true;
	if ((lhs.index1 == rhs.index2) and (lhs.index2 == rhs.index1)) return true;
	return false;
}
