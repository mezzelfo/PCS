#ifndef POINTINC
#define POINTINC

#include <iostream>

class Point2D{
  double x,y;
 public:
   Point2D(double, double);
   Point2D(double);
   Point2D();
   ~Point2D();               // distruttore
   Point2D(const Point2D &); //copia

   double get_x();
   double get_y();

   double norm2();

   Point2D operator + (const Point2D &);
   Point2D operator - (const Point2D &);
   bool operator == (const Point2D &);


   void print_p2d();


};

#endif // POINTINC
