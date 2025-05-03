/*
 * Jordan Silver
 * 2352988
 * jorsilver@chapman.edu
 * CPSC-350-04
 * A1: Robber Language Translation
*/

#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "Model.h" 

class Translator{
public:
    Translator();
    ~Translator();
    string translateEnglishWord(string w);
    string translateEnglishSentence(string s);
private:
    Model m_model;
};

#endif