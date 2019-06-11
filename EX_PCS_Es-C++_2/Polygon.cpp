#include <iostream>
#include "Polygon.hpp"
#include "Utility.hpp"

Polygon::Polygon(Edge* ev, int* vi, int la){
evett = ev;
index = vi;
n = la;
};
Polygon::Polygon(Edge* ev){
evett = ev;
index = NULL;
n = 0;
};
Polygon::Polygon(){
evett = NULL;
index = NULL;
n = 0;
};

Polygon::~Polygon(){};               // distruttore

Polygon::Polygon(const Polygon &poly){
evett = poly.evett;
index = poly.index;
n = poly.n;
};

Point2D Polygon::get_point(int i){
return evett[i].get_A();
};

Edge Polygon::get_edge(int i){
return evett[i];
};

int Polygon::num_edges(){
return n;
};

bool Polygon::ispoly(){
int i;
if (n < 3) return false;
for (i = 0; i < n; i++){
    if (ordercheck(evett[index[i%n]],evett[index[(i+1)%n]]) == 0){
        return false;
    }
}
//std::cout<<"ispoly"<<std::endl;
return true;
};

double Polygon::perimeter(){
int i;
double p = 0;
for (i = 0; i < n; i++)
    p += evett[index[i]].len();
return p;
};
double Polygon::area(){
int i;
double a = 0;
if (ispoly()){
for (i = 0; i < n; i++)
    a += (evett[index[i%n]].get_A().get_x())*(evett[index[(i+1)%n]].get_A().get_y()) - (evett[index[(i+1)%n]].get_A().get_x())*(evett[index[i%n]].get_A().get_y());
return a/2;
}
else return 0;
};
