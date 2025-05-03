/*
 * Jordan Silver, Neil Azimi
 * 2352988, 2428566
 * jorsilver@chapman.edu, nazimi@chapman.edu
 * CPSC-350-04
 * A4: The Waiting Game
*/

#ifndef SERVICE_CENTER_H
#define SERVICE_CENTER_H

#include <fstream>
#include <iostream>
#include "Office.h"
#include "PQueue.h"

class ServiceCenter{
public:
    ServiceCenter();
    ServiceCenter(const string& inputFile);
    ~ServiceCenter();
    void simulate();
    void printData();
private:
    int m_currTime;
    int m_tenMinWaits;
    int m_totCustomers;
    Office* m_offices[3];
    ListQueue<Customer*> m_arrivalQueue;
};

#endif