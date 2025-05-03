/*
 * Jordan Silver
 * 2352988
 * jorsilver@chapman.edu
 * CPSC-350-04
 * A2: Not So Super Mario World
*/

#ifndef COIN_H
#define COIN_H

#include "Element.h"

//Derived class of 'Element'
class Coin: public Element{
public:
    Coin();
    Coin(int row, int col);
    ~Coin();
};

#endif