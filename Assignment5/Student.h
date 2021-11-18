/*
Gabe Davidson
2338642
gadavidson@chapman.edu
Student.h -> Assignment5

Header file for student class
...

Sources:
- None
*/

#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>

using namespace std;

class Student{
  public:
    Student();
    Student(int time, int t);
    ~Student();

    void setTimeNeeded(int t);
    void decrementTimeNeeded();
    int getTimeNeeded();

    int getInitialTick();

    void setTimeWaited(int t);
    int getTimeWaited();

  private:
    int timeNeeded;
    int tick;
    int timeWaited;
};

#endif
