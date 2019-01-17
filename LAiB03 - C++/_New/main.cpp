#include <iostream>
#include <vector>
#include "Point.hpp"
#include "Edge.hpp"
#include "Polygon.hpp"

int main()
{
	Point A(1,2);
	Point B(0,6);
	Point C(5,6);
	Edge E1(A,B);
	Edge E2(B,C);
	Edge E3(C,A);

	std::vector<Edge> v;
	v.push_back(E1);
	v.push_back(E2);
	v.push_back(E3);

	Polygon poli(v);



	return 0;
}
