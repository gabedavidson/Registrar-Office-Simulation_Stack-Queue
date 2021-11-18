/*
Gabe Davidson
2338642
gadavidson@chapman.edu
RegistrarWindow.cpp -> Assignment5

Implementation file for the window class
Makes up a registrar window and tracks its stats

Sources:
- None
*/

#include "RegistrarWindow.h"
#include <iostream>

using namespace std;

RegistrarWindow::RegistrarWindow(){
  idleStatus = true;
  totalIdleTime = 0;
  stud = NULL;
}

RegistrarWindow::~RegistrarWindow(){
}

void RegistrarWindow::setIdleStatus(bool b){
  idleStatus = b;
}

bool RegistrarWindow::isIdle(){
  return idleStatus;
}

void RegistrarWindow::increaseIdleTime(int inc){
  totalIdleTime += inc;
}

int RegistrarWindow::getIdleTime(){
  return totalIdleTime;
}

void RegistrarWindow::setStudentAttending(Student* s){
  stud = s;
}

Student* RegistrarWindow::getStudentAttending(){
  return stud;
}

void RegistrarWindow::dismissStudent(){
  stud = NULL;
}
