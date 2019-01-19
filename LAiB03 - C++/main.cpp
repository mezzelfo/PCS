#include <iostream>
#include "Point2D.hpp"
#include "Edge.hpp"
#include "Polygon.hpp"
#include <vector>
#include <math.h>

int main()
{
    std::vector<Point2D> v = {Point2D(0,0), Point2D(0,1), Point2D(1,1), Point2D(1,0)};
    std::cout << "Inizio costruizione Poligono\n";
    Polygon P(v);
    std::cout << "Fine costruizione Poligono\n";
    std::cout<< "Perimeter: " << P.Perimeter() << std::endl;
    return 0;
}