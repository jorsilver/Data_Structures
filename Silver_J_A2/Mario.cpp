/*
 * Jordan Silver
 * 2352988
 * jorsilver@chapman.edu
 * CPSC-350-04
 * A2: Not So Super Mario World
*/

#include "Mario.h"

Mario::Mario(){}

Mario::Mario(int lives, int row, int col): Element(row, col, 'H'){
    m_lives = lives;
    m_coins = 0;
    m_powLev = 0;
    m_kills = 0;
}

Mario::~Mario(){}

//Increments 'm_coins'. If 'm_coins' = 20, increments 'm_lives' and sets 'm_coins' to 0
void Mario::collectCoin(){
    if (++m_coins == 20){
        earnLife();
        m_coins = 0;
    }
}

//Increments 'm_lives'
void Mario::earnLife(){
    m_lives++;
}

//Decrements 'm_lives' and sets 'm_kills' to 0
void Mario::loseLife(){
    m_lives--;
    m_kills = 0;
}

//If 'm_powLev' is less than 2, increments 'm_powLev'
void Mario::increasePower(){
    if (m_powLev < 2) m_powLev++;
}

//If 'm_powLev' is greater than 0, decrements 'm_powLev', otherwise decrements 'm_lives'
void Mario::decreasePower(){
    if (m_powLev > 0) m_powLev--;
    else loseLife();
}

//Increments 'm_kills'. If 'm_kills' = 7, increments 'm_lives' and resets 'm_kills' to 0
void Mario::addKill() {
    if (++m_kills == 7){
        earnLife();
        m_kills = 0;
    }
}

int Mario::getLives(){
    return m_lives;
}

int Mario::getPowLev(){
    return m_powLev;
}

int Mario::getCoins(){
    return m_coins;
}
