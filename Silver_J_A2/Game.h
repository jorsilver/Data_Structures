/*
 * Jordan Silver
 * 2352988
 * jorsilver@chapman.edu
 * CPSC-350-04
 * A2: Not So Super Mario World
*/

#ifndef WORLD_H
#define WORLD_H

#include <random>
#include <time.h>
#include "Level.h"
#include "Mario.h"
#include "Boss.h"
#include "WarpPipe.h"
#include "FileProcessor.h"

//Stores all variables and functions needed to execute game logic
class Game{
public:
    Game();
    Game(string inputFile);
    ~Game();
    void play();
    void nextElement();
    void replaceWithNothing();
    void putBack();
    void warp();
    bool fight(char type);
    string toString(const Game &g){
        ostringstream ss;
        for (int i = 0; i < g.m_totalLevs; ++i){
            ss << g.m_levels[i]->toString(*g.m_levels[i]) << endl;
        }
        return ss.str();
    }
private:
    int m_currentLev;
    int m_totalLevs;
    int m_dimension;
    int m_totalMoves;
    mt19937 m_randNumGen;
    Element *m_tempElement;
    Mario *m_mario;
    FileProcessor *m_fileProcessor;
    Level **m_levels;
};

#endif