/*
 * Jordan Silver, Neil Azimi
 * 2352988, 2428566
 * jorsilver@chapman.edu, nazimi@chapman.edu
 * CPSC-350-04
 * A4: The Waiting Game
*/

#ifndef WINDOW_H
#define WINDOW_H

#include "Customer.h"

using namespace std;

//Represents a service window in an office
//Stores variables for the current Customer being served, the idle time of the window,
//and whether the window just finished serving a Customer in the same time tick.
//Includes functions to check whether a window is idle, whether the current student is done,
//and whether the window just finished serving a student. Additionally, it provides functions
//to assign and unassign Customers to a window, decrement task time for the Customer at the window,
//increment idle time for a window, and setting the window to ready
class Window{
public:
    Window();
    ~Window();
    bool isIdle() const;
    bool studentDone() const;
    bool justFinished() const;
    int getIdleTime() const;
    void setReady();
    void incrementIdleTime();
    void decrementTaskTime();
    void enterWindow(Customer* customer);
    Customer* exitWindow();
private:
    int m_idleTime;
    bool m_justFinished;
    Customer* m_currStudent;
};

#endif