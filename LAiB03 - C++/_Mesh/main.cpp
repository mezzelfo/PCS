#include <iostream>
#include "Point.hpp"
#include "Mesh.hpp"

#include <math.h>

int main()
{
	
	Mesh M;
	std::vector<Point> cerchio;
	const double pi = 3.14159265358979323846;
	const int size = 256;
	const double dealpha = 2.0*pi/(1.0*size);
	cerchio.reserve(size);
	for (double alpha = 0; alpha < 2*M_PI; alpha+=dealpha)
	{
		Point P(cos(alpha),sin(alpha));
		cerchio.push_back(P);
	}
	int i = M.addPolygon(cerchio);
	std::cout<<"Perimetro:"<<M.getPerimeter(i)<<std::endl;
	std::cout<<"Area:"<<M.getArea(i)<<std::endl;

	return 0;
}
