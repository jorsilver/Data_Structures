/*
 * Jordan Silver
 * 2352988
 * jorsilver@chapman.edu
 * CPSC-350-04
 * A2: Not So Super Mario World
*/

#include "Element.h"

Element::Element(){
    m_row = 0;
    m_col = 0;
    m_icon = '\0';
}

Element::Element(int row, int col, char icon){
    m_row = row;
    m_col = col;
    m_icon = icon;
}

Element::Element(Element &e){
    m_row = e.getRow();
    m_col = e.getCol();
    m_icon = e.getIcon();
}

//Sets 'm_row' and 'm_col' to int values passed in
void Element::setCords(int row, int col){
    m_row = row;
    m_col = col;
}

int Element::getRow(){
    return m_row;
}

int Element::getCol(){
    return m_col;
}

char Element::getIcon(){
    return m_icon;
}

Element::~Element(){}