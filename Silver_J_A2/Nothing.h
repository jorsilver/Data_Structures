/*
 * Jordan Silver
 * 2352988
 * jorsilver@chapman.edu
 * CPSC-350-04
 * A2: Not So Super Mario World
*/

#ifndef Nothing_H
#define Nothing_H

#include "Element.h"

//Derived class of 'Element'
class Nothing: public Element{
public:
    Nothing();
    Nothing(int row, int col);
    ~Nothing();
};

#endif