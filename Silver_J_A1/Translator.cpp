/*
 * Jordan Silver
 * 2352988
 * jorsilver@chapman.edu
 * CPSC-350-04
 * A1: Robber Language Translation
*/

#include "Translator.h"

Translator::Translator(){}

Translator::~Translator(){}

//translates english word to Rövarspråket
string Translator::translateEnglishWord(string w){
    string out = "";

    for (int i = 0; i < w.length(); ++i){//loop through each char in the word
        char c = tolower(w[i]);//create a lowercase copy of the current character
        if (isalpha(c) && c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u'){//check for vowels and special characters
            out += m_model.translateSingleConsonant(w[i]);//if the char is not a vowel or special character, it is passed to method which converts it to a Rövarspråket string
        } else out += m_model.translateSingleVowel(w[i]);//if the char is a vowel or special character, it is passed to method which converts it to an english string
    }

    return out;
}

//translates english sentence to Rövarspråket
string Translator::translateEnglishSentence(string w){
    string tempWord = "";
    string output = "";

    for (int i = 0; i < w.length(); ++i){//loop through each char in the sentence
        if (w[i] != ' ' && i != (w.length() - 1)){
            tempWord += w[i];//append each char to the temp word until a space or the end of the string is found
        } else {
            output += translateEnglishWord(tempWord + w[i]);//when a space or the end of the string is found the tempword is passed to the translateEnglishWord method and the returned string is appended to the output string
            tempWord = "";//temp word is reset
        }
    }
    
    return output;
}
