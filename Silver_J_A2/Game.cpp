/*
 * Jordan Silver
 * 2352988
 * jorsilver@chapman.edu
 * CPSC-350-04
 * A2: Not So Super Mario World
*/

#include "Game.h"

Game::Game(){}

//Passes 'inputFile' to 'm_fileProcesso->read()' which returns an int array, 'worldParams'
//Wolrd is contrsucted based on the parameters in 'worldParams'
Game::Game(string inputFile): m_randNumGen(time(nullptr)){
    m_fileProcessor = new FileProcessor();
    int* worldParams = m_fileProcessor->fileRead(inputFile);
    m_totalLevs = worldParams[0];
    m_dimension = worldParams[1];
    m_currentLev = 0;
    m_totalMoves = 0;

    m_levels = new Level*[m_totalLevs];//World represented as array of Level pointers

    for (int i = 0; i < m_totalLevs; ++i){//Creating new 'Level' object for each pointer in 'm_levels[]'
        m_levels[i] = new Level(m_dimension, worldParams[3], worldParams[5], worldParams[6], worldParams[7], m_randNumGen);

        m_tempElement = m_levels[i]->getElement(m_randNumGen() % m_dimension, m_randNumGen() % m_dimension);
        while (m_tempElement->getIcon() != 'X') m_tempElement = m_levels[i]->getElement(m_randNumGen() % m_dimension, m_randNumGen() % m_dimension);//Keep moving 'm_tempElement' until a 'Nothing' object is found
        m_levels[i]->repopulate(new Boss(m_tempElement->getRow(), m_tempElement->getCol()), m_tempElement->getRow(), m_tempElement->getCol());
        delete m_tempElement;//Once a 'Nothing' object is found, a new 'Boss' object is created and stored in the array where the 'Nothing' object was found. The unused 'Nothing' object is deleted

        if (i < m_totalLevs - 1){//New 'WarpPipe' object added in every level but the last
            m_tempElement = m_levels[i]->getElement(m_randNumGen() % m_dimension, m_randNumGen() % m_dimension);
            while(m_tempElement->getIcon() != 'X') m_tempElement = m_levels[i]->getElement(m_randNumGen() % m_dimension, m_randNumGen() % m_dimension);//Keep moving 'm_tempElement' until a 'Nothing' object is found
            m_levels[i]->repopulate(new WarpPipe(m_tempElement->getRow(), m_tempElement->getCol()), m_tempElement->getRow(), m_tempElement->getCol());
            delete m_tempElement;//Once a 'Nothing' object is found, a new 'WarpPipe' object is created and stored in the array where the 'Nothing' object was found. The unused 'Nothing' object is deleted
        }
    }

    m_fileProcessor->fileWrite("\nHere is a map of Not So Super Mario World\n\n" + toString(*this) + "-----------------------------------\n");

    m_tempElement = m_levels[m_currentLev]->getElement(m_randNumGen() % m_dimension, m_randNumGen() % m_dimension);
    m_mario = new Mario(worldParams[2], m_tempElement->getRow(), m_tempElement->getCol());
    m_levels[m_currentLev]->repopulate(m_mario, m_tempElement->getRow(), m_tempElement->getCol());//New 'Mario' object created and stored at a random location in the level 1 'Object*' array
    
    delete[] worldParams;

    m_fileProcessor->fileWrite("Mario has entered the game at row " + to_string(m_mario->getRow() + 1) + ", column " + to_string(m_mario->getCol() + 1) +
    " on level 1\n\n" + m_levels[m_currentLev]->toString(*m_levels[m_currentLev]));
}

//Executes game logic
void Game::play(){
    while(m_mario->getLives() > 0){
        m_fileProcessor->fileWrite("\nMario is on level " + to_string(m_currentLev + 1) + " at row " + to_string(m_mario->getRow() + 1) + ", column " + to_string(m_mario->getCol() + 1) + " with power level " + 
        to_string(m_mario->getPowLev()) + " > ");

        char icon = m_tempElement->getIcon();

        switch (icon){
        case 'X':
            m_fileProcessor->fileWrite("The position is empty > ");
            putBack();
            break;
        case 'C':
            m_mario->collectCoin();
            m_fileProcessor->fileWrite("Mario collected a coin > ");
            replaceWithNothing();
            break;
        case 'M':
            m_mario->increasePower();
            m_fileProcessor->fileWrite("Mario ate a mushroom > ");
            replaceWithNothing();
            break;
        case 'W':
            warp();
            m_fileProcessor->fileWrite("Mario warped to level " + to_string(m_currentLev + 1) + " > ");
            break;
        case 'G':
            if (fight('G')){
                m_fileProcessor->fileWrite("Mario fought a goomba and won > ");
                replaceWithNothing();
            } else {
                m_fileProcessor->fileWrite("Mario fought a goomba and lost > ");
                putBack();
            }
            break;
        case 'K':
            if (fight('K')){
                m_fileProcessor->fileWrite("Mario fought a koopa and won > ");
                replaceWithNothing();
            } else {
                m_fileProcessor->fileWrite("Mario fought a koopa and lost > ");
                putBack();
            }
            break;
        case 'B':
            if (fight('B')){
                if (m_currentLev == m_totalLevs - 1){//Check if its the last level
                    m_fileProcessor->fileWrite("Mario fought the final boss and won");
                    goto gameOver;
                } else {
                    m_fileProcessor->fileWrite("Mario fought a boss and won, and will now warp to level" + to_string(m_currentLev + 2) + " > ");
                    warp();
                }
            } else m_fileProcessor->fileWrite("Mario fought a boss and died");
            break;
        default:
            break;
        }

        if (m_mario->getLives() == 0) goto gameOver;

        m_fileProcessor->fileWrite("Mario now has " + to_string(m_mario->getLives()) + " lives and " + to_string(m_mario->getCoins()) + " coins > ");
        m_totalMoves++;
        nextElement();
        m_fileProcessor->fileWrite(m_levels[m_currentLev]->toString(*m_levels[m_currentLev]));
    }

    gameOver:
        if (m_mario->getLives() == 0) m_fileProcessor->fileWrite("\nMario died after " + to_string(m_totalMoves) + " moves\n");
        else m_fileProcessor->fileWrite("\nMario won after " + to_string(m_totalMoves) + " moves !!!\n");
}

//Points m_tempElement to a new Element object up, down, left or right of the current location of 'm_mario', with random uniform probability (25% each)
//Moves 'm_mario' to a new location in the Element* array where the Element object was
void Game::nextElement(){
    int next = m_randNumGen() % 4;
    switch (next){
    case 0://up
        m_fileProcessor->fileWrite(" > Mario will now move up\n\n");
        m_tempElement = m_levels[m_currentLev]->getElement((m_mario->getRow() - 1 + m_dimension) % m_dimension, m_mario->getCol());
        m_levels[m_currentLev]->repopulate(m_mario, m_tempElement->getRow(), m_tempElement->getCol());
        break;
    case 1://down
        m_fileProcessor->fileWrite(" > Mario will now move down\n\n");
        m_tempElement = m_levels[m_currentLev]->getElement((m_mario->getRow() + 1 + m_dimension) % m_dimension, m_mario->getCol());
        m_levels[m_currentLev]->repopulate(m_mario, m_tempElement->getRow(), m_tempElement->getCol());
        break;
    case 2://left
        m_fileProcessor->fileWrite(" > Mario will now move left\n\n");
        m_tempElement = m_levels[m_currentLev]->getElement(m_mario->getRow(), (m_mario->getCol() - 1 + m_dimension) % m_dimension);
        m_levels[m_currentLev]->repopulate(m_mario, m_tempElement->getRow(), m_tempElement->getCol());
        break;
    case 3://right
        m_fileProcessor->fileWrite(" > Mario will now move right\n\n");
        m_tempElement = m_levels[m_currentLev]->getElement(m_mario->getRow(), (m_mario->getCol() + 1 + m_dimension) % m_dimension);
        m_levels[m_currentLev]->repopulate(m_mario, m_tempElement->getRow(), m_tempElement->getCol());
        break;
    default:
        break;
    }
}

//Passes a char to determine the type of enemy and executes that type's fight logic
//Returns true if mario wins the fight
bool Game::fight(char type){
    int rand = m_randNumGen() % 100;
    switch (type){
    case 'G':
        if (rand < 80)  {
            m_mario->addKill();
            return true;
        } else if (m_mario->getPowLev() > 0){
            m_mario->decreasePower();
            return false;
        } else if (m_mario->getLives() > 1){
            m_fileProcessor->fileWrite("Mario fought a goomba and lost but will try to fight him again > ");
            m_mario->decreasePower();
            return fight('G');
        } else{
            m_mario->decreasePower();
            return false;
        }
        break;
    case 'K':
        if (rand < 65)  {
            m_mario->addKill();
            return true;
        } else if (m_mario->getPowLev() > 0){
            m_mario->decreasePower();
            return false;
        } else if (m_mario->getLives() > 1){
            m_fileProcessor->fileWrite("Mario fought a koopa and lost but will try to fight him again > ");
            m_mario->decreasePower();
            return fight('G');
        } else{
            m_mario->decreasePower();
            return false;
        }
        break;
    case 'B':
        if (rand < 50){
            m_mario->addKill();
            return true;
        } else if (m_mario->getPowLev() > 1){
            m_fileProcessor->fileWrite("Mario fought a boss and lost but will try to fight him again > ");
            m_mario->decreasePower();
            m_mario->decreasePower();
            return fight('B');
        } else if (m_mario->getLives() > 1){
            m_fileProcessor->fileWrite("Mario fought a boss and lost but will try to fight him again > ");
            m_mario->loseLife();
            return fight('B');
        } else{
            m_mario->loseLife();
            return false;
        }
        break;    
    default:
        break;
    }
}

//Creats and stores a 'Nothing' object at m_mario's current location in the array
//Deletes the object 'm_tempElement was pointing to
void Game::replaceWithNothing(){
    m_levels[m_currentLev]->repopulate(new Nothing(m_mario->getRow(), m_mario->getCol()), m_mario->getRow(), m_mario->getCol());
    delete m_tempElement;
}

//Stores the object 'm_tempElement' is pointing to back in the array
void Game::putBack(){
    m_levels[m_currentLev]->repopulate(m_tempElement, m_mario->getRow(), m_mario->getCol());
}

//First checks if 'warp()' is being called after interacting with a 'WarpPipe' or a 'Boss'
//If called from a 'WarpPipe', 'putBack()' is called, otherwise 'replaceWithNothing()' is called
//Then 'm_currentLev' is incremented and mario's coordinates are randomized
void Game::warp(){
    if (m_tempElement->getIcon() == 'W') putBack();
    else replaceWithNothing();
    m_currentLev++;
    m_mario->setCords((m_randNumGen() % m_dimension), (m_randNumGen() % m_dimension));
}

Game::~Game(){
    delete m_fileProcessor;
    delete m_tempElement;
    for (int i = 0; i < m_totalLevs; ++i) delete m_levels[i];
    delete[] m_levels;
}