// Jordan Silver, Neil Azimi
// 2352988, 2428556
// jorsilver@chapman.edu, nazimi@chapman.edu
// CPSC - 350 - 04
// A5: LB - BST

#ifndef SCAPEGOAT_H
#define SCAPEGOAT_H

#include <cmath>
#include "TreeNode.h"

//static method for log base 3/2
static double const log32(int m){
  return log(m)/log(3.0/2.0);
}

//Scapegoat class
//Implentation for all standard BST opperations with
//additional functionality for rebuilding a subtree
//when it becomes unbalanced
template <typename T>
class ScapegoatST{
public:
  ScapegoatST();
  virtual ~ScapegoatST();
  void insert(T data);
  void remove(T data);
  bool contains(T data);
  T& find(T data);
  friend ostream& operator << (ostream& out, ScapegoatST<T>& tree){//overloaded << operator
    if (tree.m_root != NULL) out << *tree.m_root;
    return out;
  }
private:
  int m_size;
  int m_balancedMax;
  TreeNode<T>* m_root;
  
  bool isEmpty();
  double size(TreeNode<T>* subTreeRoot);
  int insertHelper(TreeNode<T>*& subTreeRoot, TreeNode<T>* newNode);
  void buildSubTree(TreeNode<T>* subTreeRoot);
  int treeToArray(TreeNode<T>* subTreeRoot, T* treeArr, int i);
  TreeNode<T>* arrayToTree(T* treeArr, int i, int f);
  bool containsHelper(TreeNode<T>* subTreeRoot, T& data);
  TreeNode<T>* findHelper(TreeNode<T>*& subTreeRoot, T& data);
};

template <typename T>
ScapegoatST<T>::ScapegoatST(): m_root(NULL), m_size(0), m_balancedMax(0){}

template <typename T>
bool ScapegoatST<T>::isEmpty(){
  return m_size == 0;
}

template <typename T>
double ScapegoatST<T>::size(TreeNode<T>* subTreeRoot){
  if (subTreeRoot){
    return size(subTreeRoot->m_left) + size(subTreeRoot->m_right) + 1.0;
  } else return 0.0;
}

//Inserts node and checks balance
template <typename T>
void ScapegoatST<T>::insert(T data){
  TreeNode<T>* newNode = new TreeNode<T>(data);
  int insertDepth = insertHelper(m_root, newNode);
  m_size++;
  m_balancedMax++;
  if (insertDepth > log32(m_balancedMax)){
    TreeNode<T>* child = newNode;
    while (size(child)/size(child->m_parent) <= 2.0/3.0){
      child = child->m_parent;
    }
    buildSubTree(child->m_parent);
  }
}

//inserts the node using preorder recursive traversal
//and returns the depth the node was inserted at
template <typename T>
int ScapegoatST<T>::insertHelper(TreeNode<T>*& subTreeRoot, TreeNode<T>* newNode){
  if(subTreeRoot == NULL){
    subTreeRoot = newNode;
    return 0;
  } else if(newNode->m_data < subTreeRoot->m_data){
    newNode->m_parent = subTreeRoot;
    return insertHelper(subTreeRoot->m_left,newNode) + 1;
  } else{
    newNode->m_parent = subTreeRoot;
    return insertHelper(subTreeRoot->m_right,newNode) + 1;
  }
}

template <typename T>
void ScapegoatST<T>::remove(T data){
  if (isEmpty()) throw runtime_error("Can't remove node, tree is empty\n");
  TreeNode<T>* target = m_root;
  while(target != NULL && target->m_data != data){
    target = (data < target->m_data)? target->m_left : target->m_right;
  }
  if(target == NULL) throw runtime_error("Node to remove not found\n");
  //'target' has no children
  if(target->m_left == NULL && target->m_right == NULL){
    if(target == m_root) m_root = NULL;//'target' is the root
    else if(target == target->m_parent->m_left) target->m_parent->m_left = NULL;//'target' is a left child
    else target->m_parent->m_right = NULL;//'target' is a right child
    target->m_parent = NULL;
    delete target;
  }
  //'target' has two children
  else if(target->m_left != NULL && target->m_right != NULL){
    TreeNode<T>* successor = target->m_right;
    while(successor->m_left != NULL) successor = successor->m_left;
    T value = successor->m_data;
    remove(value); //Remove 'successor'
    target->m_data = value; //Replace 'target''s data with 'successor''s data
  }
  //'target' has one child
  else{
    TreeNode<T>* child = (target->m_left != NULL)? target->m_left : target->m_right;
    if(target == m_root) m_root = child;
    else{
      child->m_parent = target->m_parent;
      if(target == target->m_parent->m_left) target->m_parent->m_left = child;//'target' is a left child
      else target->m_parent->m_right = child;//'target' is a right child
    }
    target->m_parent = target->m_left = target->m_right = NULL;
    delete target;
  }
  //Check the height balance
  if (m_balancedMax > 2 * --m_size){
    m_balancedMax = m_size;
    buildSubTree(m_root);
  }
}

//builds the subtree at the given subtree root
template <typename T>
void ScapegoatST<T>::buildSubTree(TreeNode<T>* subTreeRoot){
  int n = size(subTreeRoot);
  T* treeArr = new T[n];
  treeToArray(subTreeRoot, treeArr, 0);
  TreeNode<T>* subTreeParent = subTreeRoot->m_parent;
  subTreeRoot->m_parent = NULL;
  if (subTreeRoot == m_root){
    m_root = arrayToTree(treeArr, 0, n - 1);
    delete subTreeRoot;
  } else if (subTreeRoot == subTreeParent->m_left){
    subTreeParent->m_left = arrayToTree(treeArr, 0, n - 1);
    subTreeParent->m_left->m_parent = subTreeParent;
    delete subTreeRoot;
  }else{
    subTreeParent->m_right = arrayToTree(treeArr, 0, n - 1);
    subTreeParent->m_right->m_parent = subTreeParent;
    delete subTreeRoot;
  }
  delete[] treeArr;
}

//formats the tree as an array
template <typename T>
int ScapegoatST<T>::treeToArray(TreeNode<T>* subTreeRoot, T* treeArr, int i){
  if (subTreeRoot != NULL){
    i = treeToArray(subTreeRoot->m_left, treeArr, i);
    treeArr[i++] = subTreeRoot->m_data;
    return treeToArray(subTreeRoot->m_right, treeArr, i);
  } else return i;
}

//builds an tree from the array recursively by taking the median
template <typename T>
TreeNode<T>* ScapegoatST<T>::arrayToTree(T* treeArr, int i, int f){
  if (i > f) return NULL;
  else {
    int median = (f + i) / 2;
    TreeNode<T>* subTreeRoot = new TreeNode<T>(treeArr[median]);
    subTreeRoot->m_left = arrayToTree(treeArr, i, median - 1);
    if (subTreeRoot->m_left != NULL) subTreeRoot->m_left->m_parent = subTreeRoot;
    subTreeRoot->m_right = arrayToTree(treeArr, median + 1, f);
    if (subTreeRoot->m_right != NULL) subTreeRoot->m_right->m_parent = subTreeRoot;
    return subTreeRoot;
  }
}

//checks if the piece of data is contained in the tree
template <typename T>
bool ScapegoatST<T>::contains(T data){
  return containsHelper(m_root, data);//calls the recursive function
}

//preorder traversal of the nodes in the tree to check if the tree contains such data
template <typename T>
bool ScapegoatST<T>::containsHelper(TreeNode<T>* subTreeRoot, T& data){
  if(subTreeRoot == NULL){
    return false;
  } else if(data == subTreeRoot->m_data){
    return true;
  } else if(data < subTreeRoot->m_data){
    return containsHelper(subTreeRoot->m_left, data);
  } else{
    return containsHelper(subTreeRoot->m_right, data);
  }
}

//returns reference to the data in the tree
template <typename T>
T& ScapegoatST<T>::find(T data) {
  TreeNode<T>* target = findHelper(m_root, data);
  if (target) return target->m_data;
  else throw out_of_range("Node not found");
}

//recursive function that returns the pointer to the data we are looking for
template <typename T>
TreeNode<T>* ScapegoatST<T>::findHelper(TreeNode<T>*& subTreeRoot, T& data){
  if (subTreeRoot == NULL || data == subTreeRoot->m_data){
    return subTreeRoot;
  } else if(data < subTreeRoot->m_data){
    return findHelper(subTreeRoot->m_left, data);
  } else{
    return findHelper(subTreeRoot->m_right, data);
  }
}


//deconstructor
//recursive delete of the entire tree from the rootNode
//calls destructor on the root node
//which recursively calls the destructor of children
template <typename T>
ScapegoatST<T>::~ScapegoatST(){
  if(m_root) delete m_root;
}

#endif