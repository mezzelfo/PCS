#include <iostream>
#include "Point2D.hpp"
#include "Edge.hpp"
#include "Polygon.hpp"

using namespace std;

int main()
{
    Point2D pvett[4];
    Point2D A(0,0), B(6,0),C(3,3),D(0,3);
    pvett[0]=A;
    pvett[1]=B;
    pvett[2]=C;
    pvett[3]=D;

    Edge evett[4];
    Edge AB(pvett,0,1);
    Edge BC(pvett,1,2);
    Edge CD(pvett,2,3);
    Edge DA(pvett,3,0);
    Edge BD(pvett,1,3);
    evett[0] = AB;
    evett[1] = BC;
    evett[2] = CD;
    evett[3] = DA;
    evett[4] = BD;

    int index1[3]={0,4,3};
    int n1=3;

    int index2[3]={1,2,4};
    int n2=3;
    Polygon ABD(evett, index1, n1);
    Polygon BCD(evett, index2, n2);



    cout <<ABD.ispoly()<< endl;
    cout <<BCD.ispoly()<< endl;

    cout <<ABD.area()<< endl;




    return 0;
}
