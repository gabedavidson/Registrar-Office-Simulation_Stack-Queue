/*
Gabe Davidson
2338642
gadavidson@chapman.edu
RegistrarOffice.h -> Assignment5

Header file for the RegistrarOffice class
...

Sources:
- Joshua Anderson
*/

#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include "RegistrarWindow.h"
#include "Student.h"
#include "FileProcessor.h"
#include "GenQueue.h"
#include "DoublyLinkedList.h"

class RegistrarOffice{
  public:
    RegistrarOffice(string infile);
    ~RegistrarOffice();

    void simulate();

    void getNextTick();
    void getNextStudents();

    void trySendStudentsToWindow();
    void tryRemoveProcessedStudents();
    void decrementStudentTimeNeeded();
    void tryIncrementIdleTimes();

    bool endSimulation();
    bool allWindowsIdle();

    void doOutputs();
    double getMeanStudentWaitTime();
    double getMedianStudentWaitTime();
    int getLongestStudentWaitTime();
    int getNumStudentsWaitingOverTenMins();
    double getMeanWindowIdleTime();
    int getLongestWindowIdleTime();
    int getNumWindowsIdleOverFiveMins();

  private:
    FileProcessor* fp;

    GenQueue<Student*>* studentsInLine;
    RegistrarWindow * windowsOpen;
    DoublyLinkedList<Student*>* processedStudents;
    // DoublyLinkedList<int>* processedStudentTimes;

    int currentTime;
    int nextTick;
    bool fileRead;

    int totalStudentWaitTime;
    int totalStudentsAttended;
    int totalWindowsOpen;
    int totalWindowIdleTime;

    bool printInfo;
};

#endif
