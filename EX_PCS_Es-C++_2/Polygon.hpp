#ifndef POLINC
#define POLINC

#include <iostream>
#include "Edge.hpp"

class Polygon{
  Edge* evett;
  int* index;
  int n;

 public:
   Polygon(Edge*, int*, int);
   Polygon(Edge*);
   Polygon();

   ~Polygon();               // distruttore
   Polygon(const Polygon &); //copia

   // ipotizzo che il poligono sia tale da avere i lati e i loro punti ordinati.
   Point2D get_point(int);
   Edge get_edge(int);
   int num_edges();

   bool ispoly();

   double perimeter();
   double area();


};

#endif // POLINC

