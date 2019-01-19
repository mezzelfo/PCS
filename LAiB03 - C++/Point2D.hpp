#ifndef POINT2D_H
#define POINT2D_H
#include <math.h>
#include <stdexcept>
#include <iostream>

const double TOL = 1e-10;

class Point2D
{
    // Coordinate del punto
    double x,y;
public:
    // Costruttori con un numero variabile di argomenti
    Point2D();
    Point2D(double xCoord, double yCoord);

    // Distruttore
    ~Point2D();

    // Costruttore di copia
    Point2D(const Point2D& other);

    // Metodi per l'accesso alle coordinate
    double getX();
    double getY();

    // Operatori somma e differenza di punti nel piano
    friend Point2D operator+(const Point2D& A, const Point2D& B);
    friend Point2D operator-(const Point2D& A, const Point2D& B);

    // Metodo per il calcolo della norma
    double norm() const;

    // Metodi di confronto
    friend bool operator==(const Point2D& A, const Point2D& B);
    friend bool operator<(const Point2D& A, const Point2D& B);

    // Medoti di input/output
    friend std::ostream& operator<<(std::ostream& o, const Point2D& P)
    {
        o << "(" << P.x << ", " << P.y << ")";
        return o;
    }
};

#endif
