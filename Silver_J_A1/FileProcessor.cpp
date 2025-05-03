/*
 * Jordan Silver
 * 2352988
 * jorsilver@chapman.edu
 * CPSC-350-04
 * A1: Robber Language Translation
*/

#include "FileProcessor.h"

FileProcessor::FileProcessor(){}

FileProcessor::~FileProcessor(){}

//converts english text file to Rövarspråket html file
void FileProcessor::ProcessFile(string in, string out){
    ifstream fileInStream;
    ofstream fileOutStream;

    //string variables for the line being read
    //and the translated text
    string curLine;
    string newText;

    //open files
    fileInStream.open(in);
    fileOutStream.open(out);

    //create html file
    fileOutStream << "<!DOCTYPE html><html><body>";

    // check if files are open
    if (fileInStream.is_open() && fileOutStream.is_open()){
        while (getline(fileInStream, curLine)){//read through the file line by line
            fileOutStream << "<p><b>" << curLine << "</b></p>";//write each line to the html file
            newText += m_translator.translateEnglishSentence(curLine) + "<br>";//append each line to the newText string
        }

        fileOutStream << "<br><p><i>" << newText << "</i></p></body></html>";//write the newText string to the html file
    } else {
        cout << "The file could not be opened\n";//if the file cant be opened, prompt the user and exit
        exit(EXIT_FAILURE);
    }

    //close the files
    fileInStream.close();
    fileOutStream.close();
}