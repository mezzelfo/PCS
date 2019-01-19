#ifndef POLYGON_H
#define POLYGON_H

#include "Point2D.hpp"
#include "Edge.hpp"
#include <vector>
#include <set>
#include <stdexcept>
#include <iostream>

class Polygon
{
    static std::set<Edge> allEdges;
    std::vector< std::set<Edge>::iterator > myEdges;
public:
    // Costruttori
    Polygon(std::vector<Point2D>& v);
    Polygon(std::vector<Edge>& v);

    // Distruttore
    ~Polygon();

    // Costruttore di copia
    Polygon(const Polygon& other);

    // Metodi per l'accesso alle coordinate dei vertici
    std::vector<Point2D> Vertices();

    // Metodo per l'accesso al numero dei lati
    size_t edgesNum();

    // Metodo per l'accesso ai lati
    std::vector<Edge> Edges();

    // Metodo per il calcolo del perimetro
    double Perimeter();

    // Metodo per il caloclo dell'area
    double Area();
};

#endif
