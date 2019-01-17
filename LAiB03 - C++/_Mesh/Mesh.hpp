#ifndef MESH_INC
#define MESH_INC

#include <vector>
#include <math.h>
#include <iostream>
#include "Point.hpp"
#include "Edge.hpp"
#include "Polygon.hpp"

class Mesh
{
	std::vector<Point> vPoint;
	std::vector<Edge> vEdge;
	std::vector<Polygon> vPolygon;

	int addEdge(Edge&);
	double getLength(Edge);

public:
	Mesh();
	~Mesh();
	int addPoint(Point&);
	int addPolygon(std::vector<Point>&);
	void printInfo();

	std::vector<int> getVertices(int);


	double getPerimeter(int);
	double getArea(int);

	double getLength(int i) {return getLength(vEdge.at(i));}
	Point getPointA(int i) {return vPoint[vEdge.at(i).getIndex1()];}
	Point getPointB(int i) {return vPoint[vEdge.at(i).getIndex2()];}
	std::vector<Point> getVerticesCoord(int);
	Edge getLato(int iPoly, int iEdge) {return vEdge[vPolygon.at(iPoly).lati.at(iEdge)];}
};

#endif
