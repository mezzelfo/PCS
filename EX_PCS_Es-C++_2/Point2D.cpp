#include <iostream>
#include <math.h>
#include "Point2D.hpp"

Point2D::Point2D(double a, double b){
x = a;
y = b;
};
Point2D::Point2D(double a){
x = a;
y = a;
};
Point2D::Point2D(){
x = 0;
y = 0;
};
Point2D::~Point2D(){};
Point2D::Point2D(const Point2D &punto){
x = punto.x;
y = punto.y;
}

double Point2D::get_x(){
return x;
};
double Point2D::get_y(){
return y;
}

double Point2D::norm2(){
return sqrt(x*x + y*y);
};

Point2D Point2D::operator+(const Point2D &punto){
Point2D somma;
somma.x = x + punto.x;
somma.y = y + punto.y;
return somma;
};
Point2D Point2D::operator-(const Point2D &punto){
Point2D diff;
diff.x = x - punto.x;
diff.y = y - punto.y;
return diff;
};
bool Point2D::operator==(const Point2D &punto){
if ((x == punto.x)&&(y == punto.y))
    return true;
else return false;
};

void Point2D::print_p2d(){
std::cout << x << " " << y << std::endl;
}

