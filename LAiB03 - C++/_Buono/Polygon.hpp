#ifndef POLY_INC
#define POLY_INC

#include <vector>
#include "Edge.hpp"

typedef std::set<Edge>::iterator IteratorToEdge;

class Polygon
{
	std::vector<IteratorToEdge> lati;
	static std::set<Edge> EdgeSet;
public:
	Polygon() {lati.clear();}
	~Polygon() {lati.clear();}
	Polygon(std::vector<Edge>&);
	Polygon(const Polygon& o) {lati = o.lati;}

	Edge getEdge(int i) {return *lati.at(i);}
	int getNumEdge() {return int(lati.size());}

	double getPerimeter();
	std::vector<IteratorToPoint> getVertices();
	double getArea();

	static void printMem() {std::cout<<"Memorizzati "<<EdgeSet.size()<<" Edge"<<std::endl;}
	
};

#endif
