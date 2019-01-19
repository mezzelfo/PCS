#include "Point2D.hpp"

// Costruttori con un numero variabile di argomenti
Point2D::Point2D()
{
    std::cout << "Costruisco un punto vuoto\n";
    x = 0.0;
    y = 0.0;
}
Point2D::Point2D(double xCoord, double yCoord)
{
    std::cout << "Costruisco un punto di coordinate"<<xCoord<<","<<yCoord<<"\n";
    x = xCoord;
    y = yCoord;
}

// Distruttore
Point2D::~Point2D()
{
    std::cout << "Distruggo un punto"<< *this << "\n";
}

// Costruttore di copia
Point2D::Point2D(const Point2D& other)
{
    std::cout << "Copio il punto" << other << "\n";
    x = other.x;
    y = other.y;
}

// Metodi per l'accesso alle coordinate
double Point2D::getX()
{
    return x;
}
double Point2D::getY()
{
    return y;
}

// Operatori somma e differenza di punti nel piano
Point2D operator+(const Point2D& A, const Point2D& B)
{
    return Point2D(A.x+B.x, A.y+B.y);
}
Point2D operator-(const Point2D& A, const Point2D& B)
{
    return Point2D(A.x-B.x, A.y-B.y);
}

// Metodo per il calcolo della norma
double Point2D::norm() const
{
    std::cout << "Calcolo la norma di "<< *this <<"\n";
    return std::sqrt(x*x+y*y);
}

// Metodi di confronto
bool operator==(const Point2D& A, const Point2D& B)
{
    return ((std::abs(A.x-B.x)<TOL) and (std::abs(A.y-B.y)<TOL));
}
bool operator<(const Point2D& A, const Point2D& B)
{
    if(A.x < B.x) return true;
    if(A.y < B.y) return true;
    return false;
}