#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include "Edge.hpp"
#include "Point2D.hpp"

class Polygon
{
public:
    // Costruttori
    Polygon();
    Polygon(std::vector<Point2D>);
    Polygon(std::vector<Edge>);

    // Distruttore
    ~Polygon();

    // Costruttore di copia
    Polygon(const Polygon& other);

    // Metodi per l'accesso alle coordinate dei vertici
    std::vector<Point2D> Vertices();

    // Metodo per l'accesso al numero dei lati
    size_t sidesNum();

    // Metodo per l'accesso ai lati
    std::vector<Edge> Sides();

    // Metodo per il calcolo del perimetro
    double Perimeter();

    // Metodo per il caloclo dell'area
    double Area();
};

#endif
