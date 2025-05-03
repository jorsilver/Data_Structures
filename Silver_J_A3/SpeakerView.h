#ifndef SPEAKERVIEW_H
#define SPEAKERVIEW_H

#include <fstream>
#include <iostream>
#include <sstream>
#include "MonoStack.h"

using namespace std;

//Takes a file representing a seating chart and
//determines who, in each column, can see the speaker.
class SpeakerView{
public:
    SpeakerView(const string& input);
    ~SpeakerView();
    void checkSeating();
private:
    int rows;
    int cols;
    double* cellArr;
};

#endif