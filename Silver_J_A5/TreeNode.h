// Jordan Silver, Neil Azimi
// 2352988, 2428556
// jorsilver@chapman.edu, nazimi@chapman.edu
// CPSC - 350 - 04
// A5: LB - BST

#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
using namespace std;

//TreeNode class
//Stores data variable of type T
//and pointers to a parent and
//left & right child TreeNodes
template <typename T>
class TreeNode{
public:
  TreeNode(T data);
  virtual ~TreeNode();
  template <typename S>
  friend class ScapegoatST;
  friend ostream& operator << (ostream& out, TreeNode<T>& treeNode){
    if (treeNode.m_left != NULL) out << *treeNode.m_left;
    out << treeNode.m_data;
    if (treeNode.m_right != NULL) out << *treeNode.m_right;
    return out;
  }
private:
  T m_data;
  TreeNode<T>* m_left;
  TreeNode<T>* m_right;
  TreeNode<T>* m_parent;
};

template <typename T>
TreeNode<T>::TreeNode(T data): m_data(data), m_left(NULL), m_right(NULL), m_parent(NULL){}

//Recursively deletes child nodes using post order traversal
template <typename T>
TreeNode<T>::~TreeNode(){
  if(m_left != NULL) delete m_left;
  if(m_right != NULL) delete m_right;
}

#endif