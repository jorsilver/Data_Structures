/*
 * Jordan Silver, Neil Azimi
 * 2352988, 2428566
 * jorsilver@chapman.edu, nazimi@chapman.edu
 * CPSC-350-04
 * A4: The Waiting Game
*/

#ifndef PQUEUE_H
#define PQUEUE_H

#include "ListQueue.h"

template <typename T>
class PQueue: public ListQueue<T>{//INHERITS FROM LISTQUEUE
public:
    //majority of methods are inherited from listqueue class
    PQueue();//default constructor
    ~PQueue();//deconstructor
    void enqueue(T data);//enqueue method for the priority queue specifically
    friend ostream& operator << (ostream& out, const PQueue<T>& pQueue){//overloaded operator
        out << *(pQueue.m_list);
        return out;
    }
};

template <typename T>
PQueue<T>::PQueue(): ListQueue<T>(){}

template <typename T>
void PQueue<T>::enqueue(T data){
    if (!this->m_list->isEmpty()){
        int currIdx = 0;
        ListNode<T>* currNode = this->m_list->m_head;
        //ordering while loop sorts the data
        while (currNode != nullptr && data > currNode->m_data){
            currNode = currNode->m_next;
            ++currIdx;
        }
        this->m_list->addAtPos(currIdx, data);
    } else ListQueue<T>::enqueue(data);
}

template <typename T>
PQueue<T>::~PQueue(){}

#endif