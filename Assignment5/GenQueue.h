/*
Gabe Davidson
2338642
gadavidson@chapman.edu
GenQueue.h -> Assignment5

Sources:
- none
*/

#ifndef GENQUEUE_H
#define GENQUEUE_H

#include <iostream>
#include <exception>
#include "ListInterface.h"

using namespace std;

template <class T> class GenQueue{
  public:
    GenQueue(); // defualt constructor
    GenQueue(unsigned int maxSize); // overloaded construcotr
    ~GenQueue(); // destructor

    // core functions
    void insert(T data); //aka enqueue
    T remove(); // aka dequeue

    // aux/helper functions
    T peek();
    unsigned int getSize();
    bool isFull();
    bool isEmpty();
    void printArray();

  private:
    MyList<T>* myQueue;
    unsigned int mSize;
    int front;
    int rear;
};

template <class T>
GenQueue<T>::GenQueue(){
  mSize = 128;
  myQueue = new MyList<T>();
  front = 0;
  rear = 0;
}

template <class T>
GenQueue<T>::GenQueue(unsigned int maxSize){
  mSize = maxSize;
  myQueue = new MyList<T>();
  front = 0;
  rear = 0;
}

template <class T>
GenQueue<T>::~GenQueue(){
  delete myQueue;
}

template <class T>
void GenQueue<T>::insert(T data){
  if (isFull()){
    throw runtime_error("queue is full");
  }
  myQueue->append(data);
  rear %= mSize;
}

template <class T>
T GenQueue<T>::remove(){
  if (isEmpty()){
    throw runtime_error("queue is empty");
  }

  front %= mSize;
  ++front;
  return myQueue->remove();
}

template <class T>
T GenQueue<T>::peek(){
  if(isEmpty()){
    throw runtime_error("queue is empty");
  }

  T tmp = myQueue->remove();
  myQueue->prepend(tmp);
  return tmp;
}

template <class T>
unsigned int GenQueue<T>::getSize(){
  return myQueue->getLength();
}

template <class T>
bool GenQueue<T>::isFull(){
  return (myQueue->getLength() == mSize);
}

template <class T>
bool GenQueue<T>::isEmpty(){
  return (myQueue->getLength() == 0);
}

#endif
