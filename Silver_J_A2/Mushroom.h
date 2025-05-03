/*
 * Jordan Silver
 * 2352988
 * jorsilver@chapman.edu
 * CPSC-350-04
 * A2: Not So Super Mario World
*/

#ifndef MUSHROOM_H
#define MUSHROOM_H

#include "Element.h"

//Derived class of 'Element'
class Mushroom: public Element{
public:
    Mushroom();
    Mushroom(int row, int col);
    ~Mushroom();
};

#endif