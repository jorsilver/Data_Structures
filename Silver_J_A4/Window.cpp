/*
 * Jordan Silver, Neil Azimi
 * 2352988, 2428566
 * jorsilver@chapman.edu, nazimi@chapman.edu
 * CPSC-350-04
 * A4: The Waiting Game
*/

#include "Window.h"

//Default
Window::Window(): m_idleTime(0), m_justFinished(false), m_currStudent(nullptr){}

//Return true if 'm_currstudent' is a null pointer
bool Window::isIdle() const{
    return (m_currStudent == nullptr);
}

//If window is not idle return 'm_currStudent->taskDone()'
bool Window::studentDone() const{
    if (!m_currStudent) throw runtime_error("Can't call student's 'taskDone()' function because window is idle");
    return m_currStudent->taskDone();
}

//Returns true if 'm_justFinished' is true and 'm_idelTime' is 0
//Note: The bool is only true if 'm_idleTime' is 0. This is beacuse
//'setReady()' should only be called while 'm_idleTime' is 0.
//Afterwards the bool 'm_justFinished' is only set to false from 'enterWindow()'
bool Window::justFinished() const{
    return (m_justFinished && m_idleTime == 0);
}

//Getter for 'm_idleTime'
int Window::getIdleTime() const{
    return m_idleTime;
}

//Changes 'm_justFinished' to false
//This ensures, if the window was vacated in the
//same time tick, idle time will not be incremented
//If 'm_justFinished' remains false for the entire next
//time tick, the window's idle time will then be incremented
void Window::setReady(){
    m_justFinished = false;
}

//Increments 'm_idleTime'
void Window::incrementIdleTime(){
    ++m_idleTime;
}

//Decrements the current sudent's current task time
void Window::decrementTaskTime(){
    if (!m_currStudent) throw runtime_error("Can't call student's 'decrementCurrTaskTime()' function because window is idle");
    m_currStudent->decrementCurrTaskTime();
}

//Sets 'm_justFinished' to false and assigns 'm_currStudent'
//to the same Customer assigned to the Customer* passed in
void Window::enterWindow(Customer* customer){
    m_justFinished = false;
    m_currStudent = customer;
    m_currStudent->resetCurrWaitTime();
}

//Sets 'm_currStudent' to nullptr, and 'm_justFinished' to true,
//and returns the Customer* that was assigned to 'm_currStudent'
Customer* Window::exitWindow(){
    if (!m_currStudent) throw runtime_error("Can't call 'exitWindow()' because window is idle");
    Customer* currCustomer = m_currStudent;
    m_currStudent = nullptr;
    m_justFinished = true;
    return currCustomer;
}

//Destructor
Window::~Window(){}