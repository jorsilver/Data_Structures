// Jordan Silver, Neil Azimi
// 2352988, 2428556
// jorsilver@chapman.edu, nazimi@chapman.edu
// CPSC - 350 - 04
// A5: LB - BST

#ifndef STUDENT_H
#define STUDENT_H

#include "Record.h"

//Student class
//child of Record class
//stores major, gpa, and
//advisor variables
class Student: public Record{
public:
    Student(): Record(), m_major("Default"), m_gpa(-1), m_advisor(-1){}
    Student(const int& id): Record(id), m_major("Default"), m_gpa(-1), m_advisor(-1){}//overload to pass int values as 'Record' objects to tree functions
    Student(int id, string name, string level, string major, double gpa, int advisor): Record(id, name, level),
    m_major(major), m_gpa(gpa), m_advisor(advisor){}
    ~Student(){}
    int& getAdvisor();
    void changeAdvisor(int advisorNum);
    friend ostream& operator << (ostream &out, const Student &student){
        out << "ID: " << student.m_id << endl;
        out << "Name: " << student.m_name << endl;
        out << "Level: " << student.m_level << endl;
        out << "Major: " << student.m_major << endl;
        out << "GPA: " << student.m_gpa << endl;
        out << "Advisor: " << student.m_advisor << endl;
        out << "--------------------------------------------------\n";
        return out;
    }
private:
    string m_major;
    double m_gpa;
    int m_advisor;
};

int& Student::getAdvisor(){
    return m_advisor;
}

void Student::changeAdvisor(int advisorNum){
    m_advisor = advisorNum;
}

#endif