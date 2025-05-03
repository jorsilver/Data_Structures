// Jordan Silver, Neil Azimi
// 2352988, 2428556
// jorsilver@chapman.edu, nazimi@chapman.edu
// CPSC - 350 - 04
// A5: LB - BST

#ifndef DATABASE_H
#define DATABASE_H


#include <fstream>
#include "ScapegoatST.h"
#include "Student.h"
#include "Faculty.h"

//Database class
//stores scape goat trees of types
//student and faculty
//implemetation for inteacting with
//and manipulating the trees
class DataBase{
public:
    DataBase();
    ~DataBase();
    void useDateBase();
private:
    ScapegoatST<Student> m_studentRecords;
    ScapegoatST<Faculty> m_facultyRecords;
    template <typename T>
    void getValidInput(T& input);
    void addStudent();
    void addFaculty();
    void removeStudent();
    void removeFaculty();
    void findStudent();
    void findFaculty();
    void changeAdvisor();
    void removeAdvisee();
    void printStudentRecords();
    void printFacultyRecords();
};

DataBase::DataBase(){}

void DataBase::useDateBase(){
    int curChoice;
    bool done = false;
    while (!done){//while loop for choices
        cout << "\n\n--------------STUDENT AND FACULTY DATABASE----------------\n\n";
        cout << "1.  Print all students and their information(sorted by ascending ID #)\n";
        cout << "2.  Print all faculty and their information(sorted by ascending ID #)\n";
        cout << "3.  Find and display student information given the student's ID\n";
        cout << "4.  Find and display faculty information given the faculty ID\n";
        cout << "5.  Add a new student\n";
        cout << "6.  Delete a student given the ID\n";
        cout << "7.  Add a new faculty member\n";
        cout << "8.  Delete a faculty member given the ID.\n";
        cout << "9.  Change a student's advisor given the student ID and the new faculty ID.\n";
        cout << "10. Remove an advisee from a faculty member given the ID\n";
        cout << "11. Exit\n\n";
        cout << "Enter 1 - 11 to continue:\n";
        getValidInput(curChoice);

        switch (curChoice){//switch statement that enters different methods depending on input
            case 1:
                printStudentRecords();
                break;
            case 2:
                printFacultyRecords();
                break;
            case 3:
                findStudent();
                break;
            case 4:
                findFaculty();
                break;
            case 5:
                addStudent();
                break;
            case 6:
                removeStudent();
                break;
            case 7:
                addFaculty();
                break;
            case 8:
                removeFaculty();
                break;
            case 9:
                changeAdvisor();
                break;
            case 10:
                removeAdvisee();
                break;
            case 11:
                done = true;
                break;
            default:
                break;
        }

        if (curChoice != 11){
            cout << "\n\n1. Return to menu\n2. Exit database\nEnter 1 or 2 to continue\n";
            getValidInput(curChoice);
            if (curChoice == 2 && !done) done = true;
        }
    }
}

//Makes sure input is of the intended type before proceeding
template <typename T>
void DataBase::getValidInput(T& input){
    while (!(cin >> input)){
        cin.clear();
        cin.ignore(256, '\n');
        string type = (typeid(T).name()[0] == 'i')? "integer" : "double";
        cout << "Invalid input. Please enter a valid " << type << ":\n";
    }
    //If intended type is integer but double is passed,
    //the int is taken and the decimal and everything
    //after is left in the stream so we must clear the stream
    cin.clear();
    cin.ignore(256, '\n');
}

void DataBase::printStudentRecords(){
    cout << "------------STUDENTS---------------\n";
    cout << m_studentRecords;//Calls the 'ScapeGoatST' << operator
}

void DataBase::printFacultyRecords(){
    cout << "------------FACULTY---------------\n";
    cout << m_facultyRecords;//Calls the 'ScapeGoatST' << operator
}

void DataBase::findStudent(){
    int id;
    cout << "Enter Student ID: \n";
    getValidInput(id);
    if (m_studentRecords.contains(id)) cout << m_studentRecords.find(id) << endl;//If the student exists call the student's << operator
    else cout << "Student could not be found\n";
}

void DataBase::findFaculty(){
    int id;
    cout << "Enter Faculty ID: \n";
    getValidInput(id);
    if(m_facultyRecords.contains(id)) cout << m_facultyRecords.find(id) << endl;//If the faculty exists call the faculty's << operator
    else cout << "Faculty member could not be found\n";
}

void DataBase::addStudent(){
    int id, advisor;
    double gpa;
    string name, level, major;
    cout << "---------Enter Student Information-------------\n";
    cout << "Enter student ID: \n";
    getValidInput(id);
    if (!m_studentRecords.contains(id)){
        cout << "Enter name: \n";
        cin >> name;
        cout << "Enter student rank(Freshman, Sophomore...etc): \n";
        cin >> level;
        cout << "Enter major: \n";
        cin >> major;
        cout << "Enter GPA: \n";
        getValidInput(gpa);
        cout << "Enter advisor ID number: \n";
        getValidInput(advisor);
        if (m_facultyRecords.contains(advisor)){//if the faculty tree contains the advisor number
            m_facultyRecords.find(advisor).addAdvisee(id);//gets reference to the advisor with said id and adds advisee to his list
            Student student(id, name, level, major, gpa, advisor);//creates a new Student object
            m_studentRecords.insert(student);//inserts that student into the student tree
        } else cout << "Student could not be added because advisor could not be found\n";
    } else cout << "Student with this ID already exists\n";
}

void DataBase::removeStudent(){
    int studentID;
    cout << "Enter ID for the student you wish to remove: \n";
    getValidInput(studentID);
    if (m_studentRecords.contains(studentID)){//if the tree of student records contains said id
        Student student = m_studentRecords.find(studentID);//creates a new student and passes the reference of the student in tree with that ID
        int advisorID = student.getAdvisor();//gets the advisor ID of the created student
        if (m_facultyRecords.contains(advisorID)){//if the faculty records even contain that faculty
            m_facultyRecords.find(advisorID).removeAdvisee(studentID);  //then the reference to the faculty in the tree is retrieved and remove advisee is called on that faculty member to remove the student
        }
        m_studentRecords.remove(studentID);//student is removed from the student tree
    } else cout << "Student could not be found\n";
}

void DataBase::addFaculty(){
    int id;
    string name, level, department;
    cout << "---------Enter Faculty Information-------------\n";
    cout << "Enter faculty id: \n";
    getValidInput(id);
    cout << "Enter name: \n";
    cin >> name;
    cout << "Enter faculty position(Lecturer, Professor...etc): \n";
    cin >> level;
    cout << "Enter department: \n";
    cin >> department;
    if (!m_facultyRecords.contains(id)){//if the faculty doesn't already exist
        Faculty faculty(id, name, level, department);//creates a new faculty member
        m_facultyRecords.insert(faculty);//inserts the member into tree
    } else cout << "Faculty member already in database\n";
}

void DataBase::removeFaculty(){
    int id;
    cout << "Enter ID for Faculty member you wish to remove: \n";
    getValidInput(id);
    if(m_facultyRecords.contains(id)){//if the faculty exists in the tree
        Faculty faculty = m_facultyRecords.find(id);//reference to the faculty instantiates a new faculty member object
        if (faculty.getTotAdvisees() == 0 ){//checks if the fac member has any advisees
            m_facultyRecords.remove(id);//if no advisees, then the faculty is removed from the tree
        } else{
            cout << "This faculty member's advisees need to be assigned a new advisor before this faculty member can be removed\n";
        }
    }else cout << "Faculty member could not be found\n";
}

void DataBase::changeAdvisor(){
    int studentId, newFacultyId;
    cout << "Enter student ID for student whose advisor you wish to change: \n";
    getValidInput(studentId);
    if (m_studentRecords.contains(studentId)){//if the student tree contains that student
        cout << "Enter ID for faculty memeber you wish to make this student's advisor: \n";
        getValidInput(newFacultyId);
        if (m_facultyRecords.contains(newFacultyId)){//if the faculty tree contains said fac id
            m_facultyRecords.find(newFacultyId).addAdvisee(studentId);//reference to the faculty is retrieved and an advisee is added to him
            Student& student = m_studentRecords.find(studentId);//reference to the student is created
            int curFacultyID = student.getAdvisor();//the current faculty id is retrieved for students advisor
            if (curFacultyID != -1){
                m_facultyRecords.find(curFacultyID).removeAdvisee(studentId);//the current advisor gets the student taken off their advisee list
            }
            student.changeAdvisor(newFacultyId);//the student gets new faculty assigned as advisor
            cout << "Advisor succesfully changed\n";
        } else cout << "Faculty member could not be found\n";
    } else cout << "Student could not be found\n";
}

void DataBase::removeAdvisee(){
    int studentId, facultyId;
    cout << "Enter faculty ID for the faculty member whose advisee you wish to remove: \n";
    getValidInput(facultyId);
    if (m_facultyRecords.contains(facultyId)) {//if the faculty tree contains such faculty
        Faculty& faculty = m_facultyRecords.find(facultyId);//reference to the faculty is established
        cout << "Enter student ID for advisee you wish to remove: \n";
        getValidInput(studentId);
        if (faculty.hasAdvisee(studentId)){//if the faculty member even has the student as an advisee
            faculty.removeAdvisee(studentId);//the faculty member has the student removed as their advisee
            m_studentRecords.find(studentId).changeAdvisor(-1);
        } else cout << "Student could not be found\n";
    } else cout << "Faculty member could not be found\n";
}

DataBase::~DataBase(){
    ofstream out( "runLog.txt" );
    out << "------------FACULTY----------------\n";
    out << m_facultyRecords << endl;
    out << "------------STUDENTS---------------\n";
    out << m_studentRecords << endl;
}

#endif
