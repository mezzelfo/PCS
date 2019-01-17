#include "Mesh.hpp"

Mesh::Mesh()
{
	vPoint.clear();
	vEdge.clear();
	vPolygon.clear();
}

Mesh::~Mesh()
{
	vPoint.clear();
	vEdge.clear();
	vPolygon.clear();
}

int Mesh::addPoint(Point& P)
{
	for (unsigned i = 0; i < vPoint.size(); ++i)
	{
		if (vPoint[i] == P) return i;
	}
	vPoint.push_back(P);
	return int(vPoint.size()-1);
}

int Mesh::addEdge(Edge& E)
{
	for (unsigned i = 0; i < vEdge.size(); ++i)
	{
		if (vEdge[i] == E) return i;
	}
	vEdge.push_back(E);
	return int(vEdge.size()-1);
}

int Mesh::addPolygon(std::vector<Point>& v)
{
	if (vPoint.size() < v.size()) vPoint.reserve(2*v.size());
	
	std::vector<int> indiciPunti(v.size(),-1);
	for (unsigned i = 0; i < v.size(); ++i)
	{
		indiciPunti[i] = addPoint(v[i]);
	}

	std::vector<int> indiciLati(v.size(),-1);
	for (unsigned i = 0; i < v.size()-1; ++i)
	{
		Edge E(indiciPunti[i],indiciPunti[i+1]);
		indiciLati[i] = addEdge(E);
	}
	Edge E = Edge(indiciPunti[v.size()-1],indiciPunti[0]);
	indiciLati[v.size()-1] = addEdge(E);

	Polygon poli(indiciLati);
	vPolygon.push_back(poli);
	return vPolygon.size()-1;
}

void Mesh::printInfo()
{
	std::cout	<<"Mesh Info:"
				<<"\n\tI punti memorizzati sono "<<vPoint.size()
				<<"\n\tI lati memorizzati sono "<<vEdge.size()
				<<"\n\tMesh contiene "<<vPolygon.size()<<" poligoni"<<std::endl;

	for (unsigned i = 0; i < vPolygon.size(); ++i)
	{
		std::cout<<"\t\t"<<"Il Poligono #"<<i<<" ha "<<vPolygon[i].lati.size()<<" lati"<<std::endl;
		for (unsigned j = 0; j < vPolygon[i].lati.size(); ++j)
		{
			std::cout<<"\t\t\t"<<"il lato #"<<j<<": "
						<<vPoint[vEdge[vPolygon[i].lati[j]].getIndex1()]
						<<vPoint[vEdge[vPolygon[i].lati[j]].getIndex2()]
						<<" è lungo "<<getLength(vEdge[vPolygon[i].lati[j]])<<std::endl;
		}
	}
}

double Mesh::getLength(Edge e)
{
	double dx = vPoint[e.getIndex1()].getX() - vPoint[e.getIndex2()].getX();
	double dy = vPoint[e.getIndex1()].getY() - vPoint[e.getIndex2()].getY();
	return sqrt(dx*dx+dy*dy);
}

double Mesh::getPerimeter(int iPoly)
{
	double p = 0;
	for (unsigned i = 0; i < vPolygon.at(iPoly).lati.size(); ++i)
	{
		p += getLength(vEdge[vPolygon.at(iPoly).lati[i]]);
	}
	return p;
}

std::vector<int> Mesh::getVertices(int iPoly)
{
	std::vector<int> v;
	int a = vEdge[vPolygon.at(iPoly).lati[0]].getIndex1();
	if ((a == vEdge[vPolygon.at(iPoly).lati[1]].getIndex1()) or (a == vEdge[vPolygon.at(iPoly).lati[1]].getIndex2()))
	{
		v.push_back(vEdge[vPolygon.at(iPoly).lati[0]].getIndex2());
		v.push_back(vEdge[vPolygon.at(iPoly).lati[0]].getIndex1());
	}
	else
	{
		v.push_back(vEdge[vPolygon.at(iPoly).lati[0]].getIndex1());
		v.push_back(vEdge[vPolygon.at(iPoly).lati[0]].getIndex2());
	}
	
	for (unsigned i = 1; i < vPolygon.at(iPoly).lati.size()-1; ++i)
	{
		int p1 = vEdge[vPolygon.at(iPoly).lati[i]].getIndex1();
		int p2 = vEdge[vPolygon.at(iPoly).lati[i]].getIndex2();
		if (p1 == v.back())
		{
			v.push_back(p2);
		}
		else
		{
			v.push_back(p1);
		}
	}
	return v;
}

double Mesh::getArea(int iPoly)
{
	std::vector<int> punti = getVertices(iPoly);
	//Formula di Gauss per l'area
	double a = 0.0;
	for (unsigned i = 0; i < punti.size(); ++i)
	{
		a += vPoint[punti[i]].getX()*vPoint[punti[(i+1)%punti.size()]].getY();
		a -= vPoint[punti[i]].getY()*vPoint[punti[(i+1)%punti.size()]].getX();
	}
	
	return 0.5*fabs(a);
}

std::vector<Point> Mesh::getVerticesCoord(int i)
{
	std::vector<int> v = getVertices(i);
	std::vector<Point> vP;
	vP.clear();
	for (unsigned i = 0; i < v.size(); ++i)
	{
		vP.push_back(vPoint.at(v[i]));
	}
	return vP;
}
