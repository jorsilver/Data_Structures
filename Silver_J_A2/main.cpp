/*
 * Jordan Silver
 * 2352988
 * jorsilver@chapman.edu
 * CPSC-350-04
 * A2: Not So Super Mario World
*/

#include "Game.h"

//Main method creates an instance of a game object and calls its 'play' function
int main(int argc, char const *argv[]){
    Game game1(argv[1]);
    game1.play();
    return 0;
}
