/*
Gabe Davidson
2338642
gadavidson@chapman.edu
ListInterface.h -> Assignment5

Sources:
- Rahul Sura
*/

#include "DoublyLinkedList.h"
#include <iostream>

using namespace std;

template <class T> class ListInterface{
  public:
    virtual ~ListInterface() = 0;
    virtual void append(T d) const = 0;
    virtual void prepend(T d) const = 0;
    virtual void insertAfter(T d, int i) const = 0;
    virtual T remove() const = 0;
    virtual int search(T value) const = 0;
    virtual void print() const = 0;
    virtual void printReverse() const = 0;
    virtual void sort() const = 0;
    virtual bool isEmpty() const = 0;
    virtual unsigned int getLength() const = 0;
};

template <class T>
ListInterface<T>::~ListInterface(){
}

template <class T> class MyList : public ListInterface<T>{
  public:
    MyList();
    ~MyList();
    void append(T d) const;
    void prepend(T d) const;
    void insertAfter(T d, int i) const;
    T remove() const;
    int search(T value) const;
    void print() const;
    void printReverse() const;
    void sort() const;
    bool isEmpty() const;
    unsigned int getLength() const;
  private:
    DoublyLinkedList<T>* list;
};

template <class T>
MyList<T>::MyList(){
  list = new DoublyLinkedList<T>();
}

template <class T>
MyList<T>::~MyList(){
  delete list;
}

template <class T>
void MyList<T>::append(T d) const{
  list->insertBack(d);
}

template <class T>
void MyList<T>::prepend(T d) const{
  list->insertFront(d);
}

template <class T>
void MyList<T>::insertAfter(T d, int i) const{
  //
}

template <class T>
T MyList<T>::remove() const{
  return list->removeFront();
}

template <class T>
int MyList<T>::search(T value) const{
  return list->find(value);
}

template <class T>
void MyList<T>::print() const{
  //
}

template <class T>
void MyList<T>::printReverse() const{
  //
}

template <class T>
void MyList<T>::sort() const{
  //
}

template <class T>
bool MyList<T>::isEmpty() const{
  return list->isEmpty();
}

template <class T>
unsigned int MyList<T>::getLength() const{
  return list->getSize();
}
