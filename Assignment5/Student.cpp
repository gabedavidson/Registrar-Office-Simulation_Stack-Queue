/*
Gabe Davidson
2338642
gadavidson@chapman.edu
Student.cpp -> Assignment5

Implementation file for the student class
Makes up a student and tracks its stats

Sources:
- None
*/

#include "Student.h"
#include <iostream>

using namespace std;

Student::Student(){
  timeNeeded = 0;
  timeWaited = 0;
  tick = 0;
}

Student::Student(int time, int t){
  timeNeeded = time;
  tick = t;
  timeWaited = 0;
}

Student::~Student(){
}

void Student::setTimeNeeded(int t){
  timeNeeded = t;
}

void Student::decrementTimeNeeded(){
  timeNeeded = (timeNeeded > 0) ? (timeNeeded - 1) : 0;
}

int Student::getTimeNeeded(){
  return timeNeeded;
}

int Student::getInitialTick(){
  return tick;
}

void Student::setTimeWaited(int t){
  timeWaited = t;
}

int Student::getTimeWaited(){
  return timeWaited;
}
