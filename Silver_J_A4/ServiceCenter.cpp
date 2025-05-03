/*
 * Jordan Silver, Neil Azimi
 * 2352988, 2428566
 * jorsilver@chapman.edu, nazimi@chapman.edu
 * CPSC-350-04
 * A4: The Waiting Game
*/

#include "ServiceCenter.h"

//Default
ServiceCenter::ServiceCenter(): m_currTime(1), m_tenMinWaits(0), m_totCustomers(0){
    for (int i = 0; i < 3; ++i){
        m_offices[i] = nullptr;
    }
}

//Overloaded constructor opens the file from the file name passed in and reads the first three lines into 'numWindows'
//Three Office objects are created, initialized with corresponding values from 'numWindows' and 'officeOrder'
//A loop reads subsequent lines to determine how many Customers to create, initializing each Customer with
//the values on the following line. The Customer is then added to 'm_arrivalQueue'
//Once the loop has ended, 'm_totCustomers' is initialized with the size of 'm_arrivalQueue'
ServiceCenter::ServiceCenter(const string& inputFile):  m_currTime(1), m_tenMinWaits(0){
    ifstream fileInStream(inputFile);
    if (!fileInStream) throw runtime_error("The input file could not be opened");

    int numWindows[3];
    string officeOrder[3] = {"Cashier", "Financial Aid", "Registrar"};
    fileInStream >> numWindows[2] >> numWindows[0] >> numWindows[1];
    for (int i = 0; i < 3; ++i){
        m_offices[i] = new Office(officeOrder[i], numWindows[i]);
    }

    int entranceTime, numStudents;
    while (fileInStream >> entranceTime >> numStudents){
        for (int i = 0; i < numStudents; ++i){
            int timeOne, timeTwo, timeThree;
            char officeOne, officeTwo, officeThree;
            fileInStream >> timeOne >> timeTwo >> timeThree >> officeOne >> officeTwo >> officeThree;
            m_arrivalQueue.enqueue(new Customer(entranceTime, timeOne, timeTwo, timeThree, officeOne, officeTwo, officeThree));
        }
    }
    m_totCustomers = m_arrivalQueue.getSize();
}

//Executes the simulation loop, which runs until all student requests have been addressed
void ServiceCenter::simulate(){
    ListQueue<Customer*> doneQueue;
    PQueue<Customer*> transitionQueue;
    while (doneQueue.getSize() != m_totCustomers){
        //Check if there are students in 'm_arrivalQueue' who are ready to enter the service center
        //If there are, move the ready students to their corresponding first office
        while (!m_arrivalQueue.isEmpty() && m_arrivalQueue.peek()->getEntranceTime() == m_currTime){
            int nextOfficeNum = m_arrivalQueue.peek()->getCurOffice();
            m_offices[nextOfficeNum]->enterOffice(m_arrivalQueue.dequeue());
        }

        //For each office, process students currently at a window and move done students to 'transitionQueue'
        for (Office* office : m_offices) office->processStudents(transitionQueue);

        //Check if each student in 'transitionQueue' has more offices to visit
        //If they do, move the student to their correspinding next office
        //If they don't, move the student to 'doneQueue'
        while (!transitionQueue.isEmpty()){
            if (transitionQueue.peek()->visitDone()){
                if (transitionQueue.peek()->getTotWaitTime() > 10) ++m_tenMinWaits;
                doneQueue.enqueue(transitionQueue.dequeue());
            } else {
                transitionQueue.peek()->incrementCurrOffice();
                int nextOfficeNum = transitionQueue.peek()->getCurOffice();
                m_offices[nextOfficeNum]->enterOffice(transitionQueue.dequeue());
            }
        }

        //For each office, fill any empty windows,update the windows' status,
        //and increment wait time for customers in 'm_waitQueue'
        for (Office* office : m_offices) office->updateWindows();

        ++m_currTime;//Each iteration of the loop can be considered one time tick
    }
    printData();
    while (!doneQueue.isEmpty()) delete (doneQueue.dequeue());
}

//Prints mean and idle time data for each office,
//along with the number of students who waited for more than 10 mins total
//and number of windows that were idle for more than 5 mins total
void ServiceCenter::printData(){
    cout << "Service Center Data\n\n";
    int fiveMinIdles = 0;
    for (Office* office : m_offices){
        office->printOfficeData();
        fiveMinIdles += office->getFiveMinIdles();
    }
    cout << "Number of students waiting over 10 minutes across all offices: " << m_tenMinWaits
        << "\nNumber of windows idle for over 5 minutes across all offices: " << fiveMinIdles << endl;
}

//Destructor
ServiceCenter::~ServiceCenter(){
    for (Office* office : m_offices) delete office;
}