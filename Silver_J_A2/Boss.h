/*
 * Jordan Silver
 * 2352988
 * jorsilver@chapman.edu
 * CPSC-350-04
 * A2: Not So Super Mario World
*/

#ifndef BOSS_H
#define BOSS_H

#include "Element.h"

//Derived class of 'Element'
class Boss: public Element{
public:
    Boss();
    Boss(int row, int col);
    ~Boss();
};

#endif