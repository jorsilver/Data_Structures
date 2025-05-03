/*
 * Jordan Silver, Neil Azimi
 * 2352988, 2428566
 * jorsilver@chapman.edu, nazimi@chapman.edu
 * CPSC-350-04
 * A4: The Waiting Game
*/

#ifndef OFFICE_H
#define OFFICE_H

#include "Window.h"
#include "ListQueue.h"
#include "PQueue.h"

class Office{
public:
    Office();
    Office(string type, int numWindows);
    ~Office();
    int getFiveMinIdles() const;
    double calcMeanWaitTime() const;
    double calcMeanIdleTime();
    void printOfficeData();
    void enterOffice(Customer* customer);
    void fillWindow(int windowNum);
    void processStudents(PQueue<Customer*>& doneQueue);
    void updateWindows();
private:
    string m_officeType;
    int m_numWindows;
    int m_numStudents;
    int m_totIdleTime;
    int m_maxIdleTime;
    int m_totWaitTime;
    int m_maxWaitTime;
    int m_fiveMinIdles;
    Window* m_windows;
    ListQueue<Customer*> m_waitQueue;
};

#endif