/*
 * Jordan Silver
 * 2352988
 * jorsilver@chapman.edu
 * CPSC-350-04
 * A2: Not So Super Mario World
*/

#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Handles all file io operations
class FileProcessor{
public:
    FileProcessor();
    ~FileProcessor();
    int* fileRead(string inputFile);
    void fileWrite(string out);
private:
    ifstream fileInStream;
    ofstream fileOutStream;
    string line;
};

#endif