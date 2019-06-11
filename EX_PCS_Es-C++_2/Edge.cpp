#include <iostream>
#include <cmath>
#include "Edge.hpp"

Edge::Edge(Point2D* v, int a, int b){
 pvett = v;
 A = a;
 B = b;
};
Edge::Edge(Point2D* v, int a){
 pvett = v;
 A = a;
 B = 0;
};
Edge::Edge(Point2D* v){
 pvett = v;
 A = 0;
 B = 0;
};
Edge::Edge(){
pvett = NULL;
A = 0;
B = 0;
}

Edge::~Edge(){};

Edge::Edge(const Edge &lato){
pvett = lato.pvett;
A = lato.A;
B = lato.B;
};

void Edge::set_A(int index){
A = index;
};
void Edge::set_B(int index){
B = index;
};

Point2D Edge::get_A(){
return pvett[A];
};
Point2D Edge::get_B(){
return pvett[B];
};

void Edge::print_A(){
pvett[A].print_p2d();
};
void Edge::print_B(){
pvett[B].print_p2d();
};

double Edge::len(){
return sqrt(pow(pvett[A].get_x()-pvett[B].get_x(),2)+pow(pvett[A].get_y()-pvett[B].get_y(),2));
};

