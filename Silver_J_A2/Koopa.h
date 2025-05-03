/*
 * Jordan Silver
 * 2352988
 * jorsilver@chapman.edu
 * CPSC-350-04
 * A2: Not So Super Mario World
*/

#ifndef KOOPA_H
#define KOOPA_H

#include "Element.h"

//Derived class of 'Element'
class Koopa: public Element{
public:
    Koopa();
    Koopa(int row, int col);
    ~Koopa();
};

#endif