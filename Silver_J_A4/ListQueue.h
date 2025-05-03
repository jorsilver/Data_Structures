/*
 * Jordan Silver, Neil Azimi
 * 2352988, 2428566
 * jorsilver@chapman.edu, nazimi@chapman.edu
 * CPSC-350-04
 * A4: The Waiting Game
*/

#ifndef LIST_QUEUE_H
#define LIST_QUEUE_H

#include "iostream"
#include "DblList.h"

template <typename T>
class ListQueue{
public:
  ListQueue();//default constructor
  ~ListQueue();//deconstructor
  bool isEmpty() const;
  int getSize() const;
  void incrementWaitTime();//special method added for this specific implementation
  void enqueue(T data);//adds to the back of the list
  T dequeue();//removes from the front of the list
  T peek() const;//peeks the front of the list without removing a node
  friend ostream& operator << (ostream& out, const ListQueue<T>& queue){//overloaded operator
    out << *(queue.m_list);
    return out;
  }
protected:
  DblList<T>* m_list;
};

template <typename T>
ListQueue<T>::ListQueue(){ //O(1)
  m_list = new DblList<T>();
}

template <typename T>
bool ListQueue<T>::isEmpty() const{ //O(1)
  return m_list->isEmpty();
}

template <typename T>
int ListQueue<T>::getSize() const{ //O(1)
  return m_list->m_size;
}

template <typename T>
void ListQueue<T>::incrementWaitTime(){
  int size = m_list->m_size;
  for (int i = 0; i < size; ++i){
    m_list->get(i)->incrementWaitTime();
  }
}

template <typename T>
void ListQueue<T>::enqueue(T data){ //O(1)
  m_list->append(data);
}

template <typename T>
T ListQueue<T>::dequeue(){ //O(1) better tell user to check if empty first
  return m_list->removeFront();
}

template <typename T>
T ListQueue<T>::peek() const{ //O(1) what about if empty?
  return m_list->get(0);
}

template <typename T>//deconstructor
ListQueue<T>::~ListQueue(){ //O(1)
  delete m_list;
}

#endif