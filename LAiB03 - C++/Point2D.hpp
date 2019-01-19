#ifndef POINT2D_H
#define POINT2D_H

class Point2D
{
    double x,y;
public:
    // Costruttori con un numero variabile di argomenti
    Point2D();
    Point2D(double xCoord);
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
    double norm();
};

#endif
