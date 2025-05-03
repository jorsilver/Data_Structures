/*
 * Jordan Silver
 * 2352988
 * jorsilver@chapman.edu
 * CPSC-350-04
 * A2: Not So Super Mario World
*/

#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include <sstream>

using namespace std;

//Parent class for all board pieces
class Element{
public:
    Element();
    Element(int row, int col, char icon);
    Element(Element &e);
    ~Element();
    virtual int getRow();
    virtual int getCol();
    virtual char getIcon();
    virtual void setCords(int row, int col);
    string toString(const Element &e){
        ostringstream ss;
        ss << e.m_icon;
        return ss.str();
    }
protected:
    int m_row;
    int m_col;
    char m_icon;//Char representation of the Element
};

#endif