#include "Edge.hpp"

std::vector<Point> Edge::vPoint;

Edge::Edge(Point& P1, Point& P2)
{
	int found1 = -1;
	int found2 = -1;
	for(unsigned i = 0; i < vPoint.size(); i++)
	{
		if (vPoint[i] == P1) found1 = i;
		if (vPoint[i] == P2) found2 = i;
	}
	if (found1 == -1)
	{
		vPoint.push_back(P1);
		found1 = vPoint.size()-1;
	}
	if (found2 == -1)
	{
		vPoint.push_back(P2);
		found2 = vPoint.size()-1;
	}
	index1 = found1;
	index2 = found2;
}

Edge::Edge(const Edge& o)
{
	index1 = o.index1;
	index2 = o.index2;
}

double Edge::getLength()
{
	double dx = vPoint.at(index1).getX() - vPoint.at(index2).getX();
	double dy = vPoint.at(index1).getY() - vPoint.at(index2).getY();
	return sqrt(dx*dx+dy*dy);
}

bool operator==(const Edge& lhs, const Edge& rhs)
{
	if ((lhs.index1 == rhs.index1) and (lhs.index2 == rhs.index2)) return true;
	if ((lhs.index1 == rhs.index2) and (lhs.index2 == rhs.index1)) return true;
	return false;
}
