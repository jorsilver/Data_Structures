/*
 * Jordan Silver
 * 2352988
 * jorsilver@chapman.edu
 * CPSC-350-04
 * A2: Not So Super Mario World
*/

#ifndef GOOMBA_H
#define GOOMBA_H

#include "Element.h"

//Derived class of 'Element'
class Goomba: public Element{
public:
    Goomba();
    Goomba(int row, int col);
    ~Goomba();
};

#endif