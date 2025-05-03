#ifndef MONOSTACK_H
#define MONOSTACK_H

#include <cstdlib>
using namespace std;

//stack template with added implementation
//for monotonic behavior.
template <typename T>
class MonoStack{
public:
    MonoStack();
    MonoStack(int iSize, char o);
    ~MonoStack();
    int size();
    bool isEmpty();
    bool isFull();
    void push(T c);
    T pop();
    T peek();
private:
    T* stackArr;
    int count;
    int max;
    int top;
    char dir;
};


template <typename T>
MonoStack<T>::MonoStack(): top(-1), count(0), max(0), dir('i'), stackArr(nullptr){}

template <typename T>
MonoStack<T>::MonoStack(int iSize, char o): top(-1), count(0), max(iSize), dir(o){
    stackArr = new T[max];
}

template <typename T>
int MonoStack<T>::size(){
    return count;
}

template <typename T>
bool MonoStack<T>::isEmpty(){
    return (count == 0);
}

template <typename T>
bool MonoStack<T>::isFull(){
    return (count == max);
}

template <typename T>
void MonoStack<T>::push(T c){
    if(isFull()){
        T* temp = new T[2 * max];
        for(int i = 0; i < max; ++i) temp[i] = stackArr[i];
        max *= 2;
    }

    if (dir == 'i'){//popping all values larger than c
        while (stackArr[top] > c && top >= 0) pop();
    } else if (dir == 'd'){//popping all values smaller than c
        while (stackArr[top] < c && top >= 0) pop();
    }

    stackArr[++top] = c;//pushing c
    ++count;
}

template <typename T>
T MonoStack<T>::pop(){
    count--;
    return stackArr[top--];
}

template <typename T>
T MonoStack<T>::peek(){
    return stackArr[top];
}

template <typename T>
MonoStack<T>::~MonoStack(){
    delete[] stackArr;
}

#endif