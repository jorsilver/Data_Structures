/*
 * Jordan Silver
 * 2352988
 * jorsilver@chapman.edu
 * CPSC-350-04
 * A1: Robber Language Translation
*/

#ifndef MODEL_H
#define MODEL_H

#include <string>

using namespace std;

class Model{
public:
    Model();
    ~Model();
    string translateSingleConsonant(char c);
    string translateSingleVowel(char v);
};

#endif