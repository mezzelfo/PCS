#ifndef EDGE_H
#define EDGE_H
#include "Point2D.hpp"
#include <set>
#include <stdexcept>
#include <iterator>
#include <iostream>

class Edge
{
    // Insieme di tutti gli oggetti Point2D usati da tutti gli oggetti Edge
    static std::set<Point2D> Points;

    // Indici ai punti dell'insieme Points che si riferiscono ad una specifica istanza di Edge
    std::set<Point2D>::iterator A, B;
public:
    // Costruttore
    Edge(const Point2D& P1, const Point2D& P2);

    // Distruttore
    ~Edge();

    // Costuttore di copia
    Edge(const Edge& other);
    Edge& operator=(const Edge& other);

    // Metodi per l'accesso alle coordinate degli estremi
    Point2D getA() const;
    Point2D getB() const;

    // Metodi per il calcolo della lunghezza del lato
    double length() const;

    // Metodi di confronto
    static bool Connected(const Edge& E1, const Edge& E2);
    friend bool operator==(const Edge& E1, const Edge& E2);
    friend bool operator<(const Edge& E1, const Edge& E2);

    // Medoti di input/output
    friend std::ostream& operator<<(std::ostream& o, const Edge& P)
    {
        o << "(" << *P.A << ", " << *P.B << ")";
        return o;
    }
};

#endif
