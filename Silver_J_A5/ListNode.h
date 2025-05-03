// Jordan Silver, Neil Azimi
// 2352988, 2428556
// jorsilver@chapman.edu, nazimi@chapman.edu
// CPSC - 350 - 04
// A5: LB - BST

#ifndef LIST_NODE_H
#define LIST_NODE_H

#include <iostream>
using namespace std;

template <typename T>
class ListNode{
public:
  ListNode(T data);//default constructor
  virtual ~ListNode();//deconstructor
  template <typename S>
  friend class DblList;
  friend ostream& operator << (ostream& out, const ListNode<T>& node){//overloaded operator
    out << "Student " << node.m_data;
    if (node.m_next != NULL) out << ", " << *node.m_next;
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
ListNode<T>::~ListNode(){//deconstructor
  if (m_next != NULL) delete m_next;
}

#endif