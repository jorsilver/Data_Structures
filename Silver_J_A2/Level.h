/*
 * Jordan Silver
 * 2352988
 * jorsilver@chapman.edu
 * CPSC-350-04
 * A2: Not So Super Mario World
*/

#ifndef LEVEL_H
#define LEVEL_H

#include <random>
#include <algorithm>
#include "Coin.h"
#include "Mushroom.h"
#include "Goomba.h"
#include "Koopa.h"
#include "Nothing.h"

//Stores 2d array of Element pointers and all necessary functions to manipulate the array
class Level{
public:
    Level();
    Level(int dimension, int coinPrct, int goombaPcrt, int koopaPrct, int mushPcrt, mt19937& randNumGen);
    ~Level();
    void repopulate(Element* elem, int row, int col);
    Element* getElement(int row, int col);
    string toString(const Level &l){
        ostringstream ss;
        for (int i = 0; i < l.m_dimension; ++i){
            for (int j = 0; j < l.m_dimension; ++j){
                ss << l.m_levelAry[i * l.m_dimension + j]->toString(*l.m_levelAry[i * l.m_dimension + j]) << " ";
            }
            ss << endl;
        }
        return ss.str();
    }
private:
    int m_dimension;
    Element** m_levelAry;
};

#endif