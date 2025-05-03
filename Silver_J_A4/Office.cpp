/*
 * Jordan Silver, Neil Azimi
 * 2352988, 2428566
 * jorsilver@chapman.edu, nazimi@chapman.edu
 * CPSC-350-04
 * A4: The Waiting Game
*/

#include "Office.h"

//Default
Office::Office(): m_officeType("Default"), m_numWindows(1), m_totIdleTime(0),
  m_maxIdleTime(0), m_numStudents(0), m_totWaitTime(0), m_maxWaitTime(0), m_windows(nullptr){}

//Overloaded
Office::Office(string type, int numWindows): m_officeType(type), m_numWindows(numWindows),
    m_totIdleTime(0), m_maxIdleTime(0), m_numStudents(0), m_totWaitTime(0), m_maxWaitTime(0){
    m_windows = new Window[m_numWindows];
}

//Getter for 'm_fiveMinIdles'
int Office::getFiveMinIdles() const{
    return m_fiveMinIdles;
}

//Calculate and return the mean wait time for students in the office
double Office::calcMeanWaitTime() const{
    return (double)m_totWaitTime/m_numStudents;
}

//Calculate and return the mean idle time for windows in the office
//Also updates 'm_maxIdleTime' and 'm_fiveMinIdles'
double Office::calcMeanIdleTime(){
    for (int i = 0; i < m_numWindows; ++i){
        int idleTime = m_windows[i].getIdleTime();
        m_totIdleTime += idleTime;
        if (idleTime > m_maxIdleTime) m_maxIdleTime = idleTime;
        if (idleTime > 5) ++m_fiveMinIdles;
    }
    return (double)m_totIdleTime/m_numWindows;
}

//Print mean and idle time data for office
void Office::printOfficeData(){
    cout << m_officeType << ":\n";
    cout << "Mean student wait time: " << calcMeanWaitTime() << " tick(s)";
    cout << "\nMean window idle time: " << calcMeanIdleTime() << " tick(s)";
    cout << "\nLongest student wait time: " << m_maxWaitTime << " tick(s)";
    cout << "\nLongest window idle time: " << m_maxIdleTime << " tick(s)\n\n";
}

//Add customer to 'm_waitQueue' and increment 'm_numStudents'
void Office::enterOffice(Customer* customer){
    m_waitQueue.enqueue(customer);
    m_numStudents++;
}

//Update wait time variables and transfer the student at the
//front of 'm_waitQueue' to the window at the passed index
void Office::fillWindow(int windowNum){
    int currWaitTime = m_waitQueue.peek()->getCurrWaitTime();
    m_totWaitTime += currWaitTime;
    if (currWaitTime > m_maxWaitTime) m_maxWaitTime = currWaitTime;
    m_windows[windowNum].enterWindow(m_waitQueue.dequeue());
}

//Process the students currently at a window
//and move done students to 'transitionQueue'
void Office::processStudents(PQueue<Customer*>& transitionQueue){
    for (int i = 0; i < m_numWindows; ++i){
        if (!m_windows[i].isIdle()){
            m_windows[i].decrementTaskTime();
            if (m_windows[i].studentDone()){
                transitionQueue.enqueue(m_windows[i].exitWindow());
            }
        }
    }
}

//Fill empty windows,update window status and idle times, and
//increment wait time for customers in 'm_waitQueue'
void Office::updateWindows(){
    for (int i = 0; i < m_numWindows; ++i){
        if (m_windows[i].isIdle() && !m_waitQueue.isEmpty()){
            fillWindow(i);
        }
    }

    for (int i = 0; i < m_numWindows; ++i){
        if (m_windows[i].isIdle()){
            if (m_windows[i].justFinished()) m_windows[i].setReady();
            else m_windows[i].incrementIdleTime();
        }
    }

    if (!m_waitQueue.isEmpty()) m_waitQueue.incrementWaitTime();
}

//Destructor
Office::~Office(){
    delete[] m_windows;
}