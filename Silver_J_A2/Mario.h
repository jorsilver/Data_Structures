/*
 * Jordan Silver
 * 2352988
 * jorsilver@chapman.edu
 * CPSC-350-04
 * A2: Not So Super Mario World
*/

#ifndef MARIO_H
#define MARIO_H

#include "Element.h"

//Class for protagonist Mario
//Derived class of 'Element'
class Mario: public Element{
public:
    Mario();
    Mario(int lives, int row, int col);
    ~Mario();
    void collectCoin();
    void earnLife();
    void loseLife();
    void increasePower();
    void decreasePower();
    void addKill();
    int getLives();
    int getPowLev();
    int getCoins();
private:
    int m_lives;
    int m_coins;
    int m_powLev;
    int m_kills;
};

#endif