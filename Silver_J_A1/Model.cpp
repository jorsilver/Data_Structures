/*
 * Jordan Silver
 * 2352988
 * jorsilver@chapman.edu
 * CPSC-350-04
 * A1: Robber Language Translation
*/

#include "Model.h"

Model::Model(){}

Model::~Model(){}

//coverts a consonant to Rövarspråket
string Model::translateSingleConsonant(char c){
    string out = "";
    out += c;
    out += 'o';
    out += c; 
    return out;
}

//coverts a vowel to Rövarspråket
string Model::translateSingleVowel(char v){
    string out = "";
    out += v;
    return out;
}


