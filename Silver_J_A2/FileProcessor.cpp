/*
 * Jordan Silver
 * 2352988
 * jorsilver@chapman.edu
 * CPSC-350-04
 * A2: Not So Super Mario World
*/

#include "FileProcessor.h"

FileProcessor::FileProcessor(){}

//Opens the file associated with the file name passed in and
//reads each line of the file to an array of ints and
//returns the array
int* FileProcessor::fileRead(string inputFile){
    fileInStream.open(inputFile);

    if (!fileInStream.is_open()) throw runtime_error("The input file could not be opened");

    int* params = new int[8];

    int i = 0;
    
    while (getline(fileInStream, line) && i < 8) params[i++] = stoi(line);
    
    fileInStream.close();
    
    if (i < 8){
        delete[] params;
        throw runtime_error("Not enough integers in input file");
    }

    int totalElems = 0;

    for (int j = 3; j < 8; ++j) totalElems += params[j];

    if (totalElems != 100){
        delete[] params;
        throw runtime_error("The values on lines 4 - 8 do not sum to 100 so the world cannot be made");
    }
    
    return params;
}

//Writes the string passed in to a log file, "output.txt"
void FileProcessor::fileWrite(string out){
    fileOutStream.open("output.txt", fstream::app);

    if (!fileOutStream.is_open())throw runtime_error("The output file could not be opened\n");

    fileOutStream << out;

    fileOutStream.close();
}

FileProcessor::~FileProcessor(){}