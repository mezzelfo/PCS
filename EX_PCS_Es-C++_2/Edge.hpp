#ifndef EDGEINC
#define EDGEINC

#include <iostream>
#include "Point2D.hpp"

class Edge{
  int A,B;
  Point2D* pvett;
public:
    Edge(Point2D*, int, int);
    Edge(Point2D*, int);
    Edge(Point2D*);
    Edge();
    ~Edge();
    Edge(const Edge &); //copia

    void set_A(int);
    void set_B(int);

    Point2D get_A();
    Point2D get_B();

    void print_A();
    void print_B();

    double len();
};

#endif // EDGEINC
