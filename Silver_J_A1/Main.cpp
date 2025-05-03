/*
 * Jordan Silver
 * 2352988
 * jorsilver@chapman.edu
 * CPSC-350-04
 * A1: Robber Language Translation
*/

#include "FileProcessor.h"

//main method instantiates FileProcessor object and
//takes file names as command line args to pass into the file processor
int main(int argc, char const *argv[])
{
    FileProcessor fileProcessor;
    fileProcessor.ProcessFile(argv[1], argv[2]);
    return 0;
}
