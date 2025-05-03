/*
 * Jordan Silver
 * 2352988
 * jorsilver@chapman.edu
 * CPSC-350-04
 * A2: Not So Super Mario World
*/

#ifndef WARPPIPE_H
#define WARPPIPE_H

#include "Element.h"

//Derived class of 'Element'
class WarpPipe: public Element{
public:
    WarpPipe();
    WarpPipe(int row, int col);
    ~WarpPipe();
};

#endif