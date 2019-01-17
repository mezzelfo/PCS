#include "Polygon.hpp"

std::vector<Edge> Polygon::vEdge;

Polygon::Polygon(std::vector<Edge>& v)
{
	lati.clear();
	lati.resize(v.size(),-1);
	for (unsigned i = 0; i < v.size(); ++i)
	{
		for (unsigned j = 0; j < vEdge.size(); ++j) if (v[i] == vEdge[j]) lati[i] = j; 
		if (lati[i] == -1)
		{
			vEdge.push_back(v[i]);
			lati[i] = vEdge.size()-1;
		}
	}
}

std::vector<Point> Polygon::getVertices()
{
	std::vector<Point> v;
	v.reserve(lati.size());
	if ((vEdge[lati[0]].getA() == vEdge[lati[1]].getA()) or (vEdge[lati[0]].getA() == vEdge[lati[1]].getB()))
	{
		v.push_back(vEdge[lati[0]].getB());
		v.push_back(vEdge[lati[0]].getA());
	}
	else
	{
		v.push_back(vEdge[lati[0]].getA());
		v.push_back(vEdge[lati[0]].getB());
	}
	for (unsigned i = 1; i < lati.size() - 1; ++i)
	{
		if (vEdge[lati[i]].getA() == v.back()) v.push_back(vEdge[lati[i]].getB()); else v.push_back(vEdge[lati[i]].getA());
	}
	return v;
}

double Polygon::getArea()
{
	double a = 0.0;
	std::vector<Point> vP = getVertices();
	for (unsigned i = 0; i < vP.size(); ++i)
	{
		a += vP[i].getX()*vP[(i+1)%vP.size()].getY();
		a -= vP[i].getY()*vP[(i+1)%vP.size()].getX();
	}
	return 0.5*fabs(a);
}

double Polygon::getPerimeter()
{
	double p = 0.0;
	for (unsigned i = 0; i < lati.size(); ++i) p += vEdge.at(lati.at(i)).getLength();
	return p;
}
