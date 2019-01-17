#include "Edge.hpp"

Edge::Edge()
{
	index1 = -1;
	index2 = -1;
}

Edge::Edge(int i1, int i2)
{
	index1 = i1;
	index2 = i2;
}

Edge::~Edge()
{
	index1 = -1;
	index2 = -1;
}

Edge::Edge(const Edge& other)
{
	index1 = other.index1;
	index2 = other.index2;
}

bool operator==(const Edge& lhs, const Edge& rhs)
{
	if((lhs.index1 == rhs.index1)and(lhs.index2 == rhs.index2)) return true;
	if((lhs.index1 == rhs.index2)and(lhs.index2 == rhs.index1)) return true;
	return false;
}
