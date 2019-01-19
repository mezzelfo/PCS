#ifndef EDGE_H
#define EDGE_H
#include "Point2D.hpp"

class Edge
{
public:
    // Costruttori
    Edge();
    Edge(const Point2D& P);
    Edge(const Point2D& A, const Point2D& B);

    // Distruttore
    ~Edge();

    // Costuttore di copia
    Edge(const Edge& other);

    // Metodi per l'accesso alle coordinate degli estremi
    Point2D getA();
    Point2D getB();

    // Metodi per il calcolo della lunghezza del lato
    double lunghezza();
};

#endif
