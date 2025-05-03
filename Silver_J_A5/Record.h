// Jordan Silver, Neil Azimi
// 2352988, 2428556
// jorsilver@chapman.edu, nazimi@chapman.edu
// CPSC - 350 - 04
// A5: LB - BST

#ifndef RECORD_H
#define RECORD_H

#include <iostream>
using namespace std;

//Parent class for records
//stores id number, name, and level
class Record{
public:
    Record(): m_id(-1), m_name("Default"), m_level("Default"){}
    Record(const int& id): m_id(id), m_name("Default"), m_level("Default"){}//overload to pass int values as 'Record' objects to tree functions
    Record(int id, string name, string level): m_id(id), m_name(name), m_level(level){}
    virtual ~Record(){}

    bool operator == (const Record& otherRecord){return this->m_id == otherRecord.m_id;}
    bool operator != (const Record& otherRecord){return !(*this == otherRecord);}
    bool operator <= (const Record& otherRecord){return this->m_id <= otherRecord.m_id;}
    bool operator >= (const Record& otherRecord){return this->m_id >= otherRecord.m_id;}
    bool operator < (const Record& otherRecord){return this->m_id < otherRecord.m_id;}
    bool operator > (const Record& otherRecord){return this->m_id > otherRecord.m_id;}
    
    bool operator == (const int& id){return this->m_id == id;}
    bool operator != (const int& id){return !(*this == id);}
    bool operator <= (const int& id){return this->m_id <= id;}
    bool operator >= (const int& id){return this->m_id >= id;}
    bool operator < (const int& id){return this->m_id < id;}
    bool operator > (const int& id){return this->m_id > id;}

    friend bool operator == (const int& id, const Record& otherRecord ){return otherRecord.m_id == id;}
    friend bool operator != (const int& id, const Record& otherRecord ){return !(((Record)otherRecord) == id);}
    friend bool operator <= (const int& id, const Record& otherRecord ){return otherRecord.m_id <= id;}
    friend bool operator >= (const int& id, const Record& otherRecord ){return otherRecord.m_id >= id;}
    friend bool operator < (const int& id, const Record& otherRecord ){return otherRecord.m_id < id;}
    friend bool operator > (const int& id, const Record& otherRecord ){return otherRecord.m_id > id;}
protected:
    int m_id;
    string m_name;
    string m_level;
};

#endif