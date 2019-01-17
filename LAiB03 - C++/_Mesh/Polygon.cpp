#include "Polygon.hpp"

Polygon::Polygon()
{
	lati.clear();
}

Polygon::Polygon(std::vector<int> l)
{
	lati = l;
}

Polygon::~Polygon()
{
	lati.clear();
}

Polygon::Polygon(const Polygon& other)
{
	lati = other.lati;
}
