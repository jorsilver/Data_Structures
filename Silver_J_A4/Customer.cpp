/*
 * Jordan Silver, Neil Azimi
 * 2352988, 2428566
 * jorsilver@chapman.edu, nazimi@chapman.edu
 * CPSC-350-04
 * A4: The Waiting Game
*/

#include "Customer.h"

//Default
Customer::Customer(): m_entranceTime(1), m_currWaitTime(0), m_totWaitTime(0), m_currOffice(0), m_taskTimes{5, 5, 5}, m_officeOrder{'R', 'C', 'F'}{}

//Overloaded
Customer::Customer(int entranceTime, int timeOne, int timeTwo, int timeThree, char officeOne, char officeTwo, char officeThree): 
    m_entranceTime(entranceTime), m_currWaitTime(0), m_totWaitTime(0), m_currOffice(0), m_taskTimes{timeOne, timeTwo, timeThree},
    m_officeOrder{officeOne, officeTwo, officeThree}{
}

//Return true if 'm_taskTimes[m_currOffice]' has reached zero
bool Customer::taskDone() const{
    return (m_taskTimes[m_currOffice] == 0);
}

//Return true if all values in 'm_taskTimes' have reached zero
bool Customer::visitDone() const{
    for (int taskTime : m_taskTimes){
        if (taskTime != 0) return false;
    }
    return true;
}

//Getter for 'm_entranceTime'
int Customer::getEntranceTime() const{
    return m_entranceTime;
}

//Getter for 'm_currWaitTime'
int Customer::getCurrWaitTime() const{
    return m_currWaitTime;
}

//Getter for 'm_totWaitTime'
int Customer::getTotWaitTime() const{
    return m_totWaitTime;
}

//Getter for 'm_m_taskTimes[m_currOffice]'
int Customer::getCurrTaskTime() const{
    return m_taskTimes[m_currOffice];
}

//Returns the index of current office but based on 
//the indexing of 'm_offices' in 'ServiceCenter'
int Customer::getCurOffice() const{
    char currOffice = m_officeOrder[m_currOffice];
    if (currOffice == 'C') return 0;
    else if (currOffice == 'F') return 1;
    else return 2;
}

//Increment 'm_currOffice'
void Customer::incrementCurrOffice(){
    ++m_currOffice;
}

//Increment 'm_currWaitTime' and 'm_totWaitTime'
void Customer::incrementWaitTime(){
    ++m_currWaitTime;
    ++m_totWaitTime;
}

//Reset 'm_currWaitTime' to zero
void Customer::resetCurrWaitTime(){
    m_currWaitTime = 0;
}

//Decrement 'm_taskTimes[m_currOffice]'
void Customer::decrementCurrTaskTime(){
    --m_taskTimes[m_currOffice];
}

//Destructor
Customer::~Customer(){}