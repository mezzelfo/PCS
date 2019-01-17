#ifndef POLY_INC
#define POLY_INC

#include <vector>
#include "Edge.hpp"

class Polygon
{
	std::vector<int> lati;
	static std::vector<Edge> vEdge;
public:
	Polygon() {lati.clear();}
	~Polygon() {lati.clear();}
	Polygon(std::vector<Edge>&);
	Polygon(const Polygon& o) {lati = o.lati;}

	Edge getEdge(int i) {return vEdge.at(lati.at(i));}
	int getNumEdge() {return int(lati.size());}
	std::vector<Point> getVertices();

	double getArea();
	double getPerimeter();
};

#endif
