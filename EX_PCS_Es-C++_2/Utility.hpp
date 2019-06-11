#ifndef UTIINC
#define UTIINC

#include <iostream>
#include "Edge.hpp"

int ordercheck(Edge AB,Edge BC){
if (AB.get_B() == BC.get_A())
    return 1;
else if (AB.get_B() == BC.get_B())
    return -1;
else if (AB.get_A() == BC.get_A())
    return 2;
else if (AB.get_A() == BC.get_B())
    return -2;
else return 0;
};

#endif
