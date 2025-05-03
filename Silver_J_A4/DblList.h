/*
 * Jordan Silver, Neil Azimi
 * 2352988, 2428566
 * jorsilver@chapman.edu, nazimi@chapman.edu
 * CPSC-350-04
 * A4: The Waiting Game
*/

#ifndef DBL_LIST_H
#define DBL_LIST_H

#include <iostream>
#include "ListNode.h"

template <typename T> 
class DblList{
public:
    DblList();//default constructor
    ~DblList();//deconstructor
    bool isEmpty() const;
    int getSize() const;
    bool contains(T data) const;//returns boolean to check if the list contains the value
    int find(T data) const;//returns the position of the node that contains the value T
    T get(int pos) const;//retrieves the value at a position
    void append(T data);//adds to the end of the list
    void prepend(T data);//adds to the front of the list
    void addAtPos(int pos, T data);//adds to a certain position on the list
    T removeBack();//removes the back node
    T removeFront();//removes the front node
    T removeAtPos(int pos);//removes the node at a certain position
    template <typename S>
    friend class ListQueue;
    template <typename S>
    friend class PQueue;
    friend ostream& operator << (ostream& out, const DblList<T>& list){//operator overloaded
        ListNode<T>* current = list.m_head;
        int pos = 1;
        while (current){
            out << "| (" << pos++ << ") : " << *current << " |";
            current = current->getNext();
        }
        out << endl;
        return out;
    }
private:
    unsigned int m_size;
    ListNode<T>* m_head;
    ListNode<T>* m_tail;
};

template <typename T>
DblList<T>::DblList(): m_size(0), m_head(nullptr), m_tail(nullptr){}//default constructor

template <typename T>
bool DblList<T>::isEmpty() const{
  return (m_size == 0);
}

template <typename T>
int DblList<T>::getSize() const{
  return m_size;
}

template <typename T>
bool DblList<T>::contains(T data) const{
    bool found = false;
    ListNode<T>* curr = m_head;
    while (curr){
        if (data == curr->m_data){
            found = true;
            break;
        }
        curr = curr->m_next;
    }
    return found;
}

template <typename T>
int DblList<T>::find(T data) const{
    if (!contains(data)) throw runtime_error("Node not found");
    int currPos = 0;
    ListNode<T>* curr = m_head;
    while (curr->m_data != data){
        curr = curr->m_next;
        ++currPos;
    }
    return currPos;
}

template <typename T>
T DblList<T>::get(int pos) const{
    if (isEmpty()) throw runtime_error("The list is empty can't get at position " + to_string(pos) + "\n");
    if (pos < 0 || pos >= m_size) throw runtime_error("Can't get at position " + to_string(pos) + ", invalid position\n");
    int currPos = 0;
    ListNode<T>* curr = m_head;
    while (currPos++ != pos) curr = curr->m_next;
    return curr->m_data;
}

template <typename T>
void DblList<T>::append(T data){
    ListNode<T>* newNode = new ListNode<T>(data);
    if (isEmpty()) m_head = newNode;
    else{
        m_tail->m_next = newNode;
        newNode->m_prev = m_tail;
    }
    m_tail = newNode;
    ++m_size;
}

template <typename T>
void DblList<T>::prepend(T data){
    ListNode<T>* newNode = new ListNode<T>(data);
    if (isEmpty()) m_tail = newNode;
    else{
        m_head->m_prev = newNode;
        newNode->m_next = m_head;
    }
    m_head = newNode;
    ++m_size;
}

template <typename T>
void DblList<T>::addAtPos(int pos, T data){
    if (pos < 0 || pos > m_size) throw runtime_error("Can't add at " + to_string(pos) + ", invalid position\n");
    if (isEmpty()) append(data);
    else if (pos == 0) prepend(data);
    else if (pos == m_size) append(data);
    else{
        ListNode<T>* curr = m_head;
        int currPos = 0;
        while (currPos++ != pos) curr = curr->m_next;
        ListNode<T>* newNode = new ListNode<T>(data);
        curr->m_prev->m_next = newNode;
        newNode->m_prev = curr->m_prev;
        curr->m_prev = newNode;
        newNode->m_next = curr;
        ++m_size;
    }
}

template <typename T>
T DblList<T>::removeBack(){
    if (isEmpty()) throw runtime_error("The list is empty, can't remove back");
    T data = m_tail->m_data;
    if (m_size == 1){
        delete m_head;
        m_head = nullptr;
        m_tail = nullptr;
    }else{
        m_tail = m_tail->m_prev;
        delete m_tail->m_next;
        m_tail->m_next = nullptr;
    }
    --m_size;
    return data;
}

template <typename T>
T DblList<T>::removeFront(){
    if (isEmpty()) throw runtime_error("The list is empty, can't remove front");
    T data = m_head->m_data;
    if (m_size == 1){
        delete m_tail;
        m_tail = nullptr;
        m_head = nullptr;
    }else{
        m_head = m_head->m_next;
        delete m_head->m_prev;
        m_head->m_prev = nullptr;
    }
    --m_size;
    return data;
}

template <typename T>
T DblList<T>::removeAtPos(int pos){
    if (isEmpty()) throw runtime_error("The list is empty, can't remove at position " + to_string(pos));
    if (pos < 0 || pos >= m_size) throw runtime_error("Can't remove at " + to_string(pos) + ", invalid position\n");
    T data;
    if (pos == 0) data = removeFront();
    else if (pos == m_size - 1) data = removeBack();
    else{
        ListNode<T>* curr = m_head;
        int currPos = 0;
        while (currPos++ != pos) curr = curr->m_next;
        data = curr->m_data;
        curr->m_prev->m_next = curr->m_next;
        curr->m_next->m_prev = curr->m_prev;
        delete curr;
        --m_size;
    }
    return data;
}

template <typename T>//deconstructor
DblList<T>::~DblList(){//check if this works for empty list
    ListNode<T>* curr = m_head;
    while (curr){
        ListNode<T>* target = curr;
        curr = curr->m_next;
        delete target;
    }
    m_size = 0;
    m_head = nullptr;
    m_tail = nullptr;
}

#endif