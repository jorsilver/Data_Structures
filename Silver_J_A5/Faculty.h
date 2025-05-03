// Jordan Silver, Neil Azimi
// 2352988, 2428556
// jorsilver@chapman.edu, nazimi@chapman.edu
// CPSC - 350 - 04
// A5: LB - BST

#ifndef FACULTY_H
#define FACULTY_H

#include "Record.h"
#include "DblList.h"

//Faculty class
//child of Record class
//stores department, and total advisors variables
//and pointer to array of advsisees
class Faculty: public Record{
public:
    Faculty(): Record(), m_department("Default"){}
    Faculty(const int& id): Record(id), m_department("Default"){}//overload to pass int values as 'Record' objects to tree functions
    Faculty(int id, string name, string level, string department): Record(id, name, level), m_department(department){}    
    ~Faculty(){}
    int getTotAdvisees();
    bool hasAdvisee(int id);
    void addAdvisee(int id);
    void removeAdvisee(int id);
    friend ostream& operator << (ostream &out, const Faculty &faculty){
        out << "ID: " << faculty.m_id << endl;
        out << "Name: " << faculty.m_name << endl;
        out << "Level: " << faculty.m_level << endl;
        out << "Department: " << faculty.m_department << endl;
        out << "Advisees: " << faculty.m_advisees;
        out << " \n--------------------------------------------------\n";
        return out;
    }
private:
    string m_department;
    DblList<int> m_advisees;
};

int Faculty::getTotAdvisees(){
    return m_advisees.getSize();
}

bool Faculty::hasAdvisee(int id){
    return m_advisees.contains(id);
}

void Faculty::addAdvisee(int id){
    m_advisees.prepend(id);
}

void Faculty::removeAdvisee(int id){
    int position = m_advisees.find(id);
    m_advisees.removeAtPos(position);
}

#endif