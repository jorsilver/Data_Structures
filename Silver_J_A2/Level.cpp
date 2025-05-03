/*
 * Jordan Silver
 * 2352988
 * jorsilver@chapman.edu
 * CPSC-350-04
 * A2: Not So Super Mario World
*/

#include "Level.h"

Level::Level(){}

//Takes in parameters for level dimension, perecentage of each Element type and a random number generator
//Creates and populates 2d array of Element pointers based on the paramters passed
//then adjusts the coordinate member variables for each Element
Level::Level(int dimension, int cointPrct, int goombaPrct, int koopaPrct, int mushPrct, mt19937& randNumGen): m_dimension(dimension){
    int coins = cointPrct * dimension * dimension / 100;
    int goombas = goombaPrct * dimension * dimension / 100;
    int koopas = koopaPrct * dimension * dimension / 100;
    int mushrooms = mushPrct * dimension * dimension / 100;

    m_levelAry = new Element*[dimension * dimension];

    Element** memLoc = m_levelAry;

    for (int i = 0; i < dimension; ++i){
        for (int j = 0; j < dimension; ++j, ++memLoc){
            if (coins-- > 0) m_levelAry[i * dimension + j] = new Coin(i,j);
            else if (goombas-- > 0) m_levelAry[i * dimension + j] = new Goomba(i,j);
            else if (koopas-- > 0) m_levelAry[i * dimension + j] = new Koopa(i,j);
            else if (mushrooms-- > 0) m_levelAry[i * dimension + j] = new Mushroom(i,j);
            else m_levelAry[i * dimension + j] = new Nothing(i,j);
        }
    }

    shuffle(m_levelAry, memLoc, randNumGen);
    
    for (int i = 0; i < dimension; ++i){
        for (int j = 0; j < dimension; ++j) m_levelAry[i * dimension + j]->setCords(i,j);
    }
}

//Sets the Element pointer in the array, at the coordinates passed in, to the Element passed in
void Level::repopulate(Element* elem, int row, int col){
    m_levelAry[row * m_dimension + col] = elem;
    elem->setCords(row,col);
}

//Returns the Element pointer in the array at the coordinates passed in
Element* Level::getElement(int row, int col){
    return m_levelAry[row * m_dimension + col];
}

Level::~Level() {
    for (int i = 0; i < m_dimension * m_dimension; ++i) delete m_levelAry[i];
    delete[] m_levelAry;
}