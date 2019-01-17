#ifndef POLYGON_INC
#define POLYGON_INC

#include <vector>

class Polygon
{
	std::vector<int> lati;
	Polygon();
	Polygon(std::vector<int>);
	int getNumberOfSides() {return lati.size()-1;};

public:
	~Polygon();
	Polygon(const Polygon&);

	friend class Mesh;
};

#endif
