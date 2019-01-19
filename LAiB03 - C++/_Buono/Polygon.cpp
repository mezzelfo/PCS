#include "Polygon.hpp"

std::set<Edge> Polygon::EdgeSet;

Polygon::Polygon(std::vector<Edge>& v)
{
	lati.resize(v.size());
	for (int i = 0; i < int(v.size()); ++i) lati[i] = EdgeSet.insert(v[i]).first;
}

double Polygon::getPerimeter()
{
	double p = 0.0;
	for (int i = 0; i < int(lati.size()); ++i) p += (lati.at(i))->getLength();
	return p;
}

std::vector<IteratorToPoint> Polygon::getVertices()
{
	std::vector<IteratorToPoint> v;
	v.reserve(lati.size());
	if ((lati[0]->getPtrToA() == lati[1]->getPtrToA()) or (lati[0]->getPtrToA() == lati[1]->getPtrToB()))
	{
		v.push_back(lati[0]->getPtrToB());
		v.push_back(lati[0]->getPtrToA());
	}
	else
	{
		v.push_back(lati[0]->getPtrToA());
		v.push_back(lati[0]->getPtrToB());
	}
	for (int i = 1; i < int(lati.size()) - 1; ++i)
	{
		if (lati[i]->getPtrToA() == v.back()) v.push_back(lati[i]->getPtrToB()); else v.push_back(lati[i]->getPtrToA());
	}
	return v;
}

double Polygon::getArea()
{
	double a = 0.0;
	std::vector<IteratorToPoint> vP = getVertices();
	for (unsigned i = 0; i < vP.size(); ++i)
	{
		a += vP[i]->getX() * vP[(i+1)%vP.size()]->getY();
		a -= vP[i]->getY() * vP[(i+1)%vP.size()]->getX();
	}
	return 0.5*fabs(a);
}
