/*
 * Jordan Silver, Neil Azimi
 * 2352988, 2428566
 * jorsilver@chapman.edu, nazimi@chapman.edu
 * CPSC-350-04
 * A4: The Waiting Game
*/

#ifndef LIST_NODE_H
#define LIST_NODE_H

using namespace std;

template <typename T>
class ListNode{
public:
  ListNode(T data);//default constructor
  virtual ~ListNode();//deconstructor
  ListNode<T>* getNext() const;//gets the next node as a pointer
  template <typename S>
  friend class DblList;
  template <typename S>
  friend class PQueue;
  friend ostream& operator << (ostream& out, const ListNode<T>& node){//overloaded operator
    out << *(node.m_data);
    return out;
  }
private:
  T m_data;
  ListNode<T>* m_next;
  ListNode<T>* m_prev;
};

template <typename T>
ListNode<T>::ListNode(T data): m_data(data), m_next(nullptr), m_prev(nullptr){}//overloaded constructor

template <typename T>
ListNode<T>* ListNode<T>::getNext() const{//gets the next node
  return this->m_next;
}

template <typename T>
ListNode<T>::~ListNode(){//deconstructor
  m_next = nullptr;
  m_prev = nullptr;
}

#endif