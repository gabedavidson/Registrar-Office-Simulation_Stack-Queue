/*
Gabe Davidson
2338642
gadavidson@chapman.edu
RegistrarWindow.cpp -> Assignment5

Header file for the window class
...

Sources:
- None
*/

#ifndef REGISRARWINDOW_H
#define REGISTRARWINDOW_H

#include <iostream>
#include "Student.h"

class RegistrarWindow{
  public:
    RegistrarWindow();
    ~RegistrarWindow();

    void setIdleStatus(bool b);
    bool isIdle();

    void increaseIdleTime(int inc);
    int getIdleTime();

    void setStudentAttending(Student* s);
    Student* getStudentAttending();
    void dismissStudent();

  private:
    bool idleStatus;
    int totalIdleTime;
    Student* stud;
};

#endif
