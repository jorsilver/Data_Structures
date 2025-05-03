/*
 * Jordan Silver
 * 2352988
 * jorsilver@chapman.edu
 * CPSC-350-04
 * A1: Robber Language Translation
*/

#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include "Translator.h"
#include <iostream>
#include <fstream>

class FileProcessor{
public:
    FileProcessor();
    ~FileProcessor();
    void ProcessFile(string in, string out);
private:
    Translator m_translator;
};

#endif