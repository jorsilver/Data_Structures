/*
 * Jordan Silver, Neil Azimi
 * 2352988, 2428566
 * jorsilver@chapman.edu, nazimi@chapman.edu
 * CPSC-350-04
 * A4: The Waiting Game
*/

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>

using namespace std;

//Represents a student vistiting the student service center
//Stores variables for entrance time, current wait time, total wait time, current office,
//task times for each office, and office visiting order, along with functions to get and set those variables
//Also includes overloaded comparison operators for sorting customers based on their current office
class Customer{
public:
    Customer();//default constructor
    Customer(int entranceTime, int timeOne, int timeTwo, int timeThree, char officeOne, char officeTwo, char officeThree);//overloaded constructor
    ~Customer();//deconstructor
    bool taskDone() const;
    bool visitDone() const;
    int getEntranceTime() const;
    int getCurrWaitTime() const;
    int getTotWaitTime() const;
    int getCurrTaskTime() const;
    int getCurOffice() const;
    void incrementCurrOffice();
    void incrementWaitTime();
    void resetCurrWaitTime();
    void decrementCurrTaskTime();
    bool operator > (const Customer* otherCustomer){
        return this->m_officeOrder[this->m_currOffice] > otherCustomer->m_officeOrder[otherCustomer->m_currOffice];
    }
    bool operator < (const Customer* otherCustomer){
        return this->m_officeOrder[this->m_currOffice] < otherCustomer->m_officeOrder[otherCustomer->m_currOffice];
    }
private:
    int m_entranceTime;
    int m_currWaitTime;
    int m_totWaitTime;
    int m_currOffice;
    int m_taskTimes[3];
    char m_officeOrder[3];
};

#endif