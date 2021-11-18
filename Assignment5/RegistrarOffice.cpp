/*
Gabe Davidson
2338642
gadavidson@chapman.edu
RegistrarOffice -> Assignment5

Implementation file for the RegistrarOffice class
Tracks times and windows and moves students accordingly between queue, windows, and then removes
Calculates statistics on wait times and idle times

Sources:
- Joshua Anderson
-
*/

#include "RegistrarOffice.h"
#include "FileProcessor.h"
#include "Student.h"
#include "GenQueue.h"
#include "DoublyLinkedList.h"
#include <iostream>

using namespace std;

RegistrarOffice::RegistrarOffice(string infile){
  // initialize studentsInLine queue
  studentsInLine = new GenQueue<Student*>();
  // intialize processedStudents dll
  processedStudents = new DoublyLinkedList<Student*>();
  // initialize fp FileProcessor
  fp = new FileProcessor('r', infile);

  // initialize windowsOpen arr
  totalWindowsOpen = std::stoi(fp->readFileLine());
  windowsOpen = new RegistrarWindow[totalWindowsOpen];
  for (int i = 0; i < totalWindowsOpen; ++i){
    RegistrarWindow hold;
    windowsOpen[i] = hold;
  }

  currentTime = 0;
  nextTick = 0;
  fileRead = false;

  totalStudentWaitTime = 0;
  totalStudentsAttended = 0;
  totalWindowIdleTime = 0;

  printInfo = false;
}

RegistrarOffice::~RegistrarOffice(){
  delete studentsInLine;
  delete [] windowsOpen;
  delete processedStudents;
}

void RegistrarOffice::simulate(){
  getNextTick();

  while (true){
    // increment current time
    ++currentTime;
    if (printInfo){
      cout << "CURR TICK = " << currentTime << endl;
    }

    // add students to queue if...
    if (currentTime == nextTick){
      if (!fileRead){
        getNextStudents();
        getNextTick();
      }
    }

    // attempt to add students from queue to windows
    // also calculates time waited (current tick - tick entered queue)
    trySendStudentsToWindow();

    // decremenet time needed (student time waited is calculated at end)
    decrementStudentTimeNeeded();

    // incremenet idle time
    tryIncrementIdleTimes();

    // remove processed students from windows
    tryRemoveProcessedStudents();

    // test if should end simulation
    if (endSimulation()){
      break;
    }
  }

  // cout results
  doOutputs();
}

/*
 The following are runtime methods which update and check the
 condition of the simulation.
*/

// Reads a line from the file and sets it as the next clock tick to check for
void RegistrarOffice::getNextTick(){
  // cout << "getNextTick" << endl;
  try{
    nextTick = std::stoi(fp->readFileLine());
  }
  catch (...){
    fileRead = true;
    fp->closeReader();
  }


  if (printInfo){
    cout << "Next tick: " << nextTick << endl;
  }
}

// When current time and next tick are equal, adds as many students
//      to the queue given wait time
void RegistrarOffice::getNextStudents(){
  // cout << "getNextStudents" << endl;
  if (fp->endOfReadFile()){
    return;
  }
  int studs = std::stoi(fp->readFileLine());
  for (int i = 0; i < studs; ++i){
    Student* tmp = new Student(std::stoi(fp->readFileLine()), currentTime);
    studentsInLine->insert(tmp);

    if (printInfo){
      cout << "Added student to queue with time needed: " << tmp->getTimeNeeded() << endl;
    }
  }
}

// Attemps to send students from queue to an open window
void RegistrarOffice::trySendStudentsToWindow(){
  // cout << "trySendStudentsToWindow" << endl;
  for (int i = 0; i < totalWindowsOpen; ++i){
    // a window must be open and the queue must not be empty
    if (windowsOpen[i].isIdle() && !studentsInLine->isEmpty()){
      Student *hold = studentsInLine->remove();
      hold->setTimeWaited(currentTime - hold->getInitialTick());
      totalStudentWaitTime += hold->getTimeWaited();
      windowsOpen[i].setStudentAttending(hold);
      windowsOpen[i].setIdleStatus(false);
      totalStudentsAttended += 1;

      if (printInfo){
        cout << "Student sent to window from queue with time waited: " << hold->getTimeWaited() << endl;
      }
    }
  }
}

// Attemps to remove students from windows whose time needed is zero
void RegistrarOffice::tryRemoveProcessedStudents(){
  // cout << "tryRemoveProcessedStudents" << endl;
  for (int i = 0; i < totalWindowsOpen; ++i){
    if (windowsOpen[i].getStudentAttending() != NULL){
      if (windowsOpen[i].getStudentAttending()->getTimeNeeded() == 0){
        Student *tmp = windowsOpen[i].getStudentAttending();
        windowsOpen[i].dismissStudent();
        processedStudents->insertFront(tmp);
        windowsOpen[i].setIdleStatus(true);

        if (printInfo){
          cout << "Student removed from window at tick: " << currentTime << endl;
        }
      }
    }
  }
}

// Decrements time needed for students at windows
void RegistrarOffice::decrementStudentTimeNeeded(){
  // cout << "decrementStudentTimeNeeded" << endl;
  for (int i = 0; i < totalWindowsOpen; ++i){
    if (!windowsOpen[i].isIdle()){
      windowsOpen[i].getStudentAttending()->decrementTimeNeeded();
    }

    if (printInfo){
      cout << "Decremented student time needed." << endl;
    }
  }
}

// Attemps to increment idle time for windows who are idle
void RegistrarOffice::tryIncrementIdleTimes(){
  // cout << "tryIncrementIdleTimes" << endl;
  for (int i = 0; i < totalWindowsOpen; ++i){
    if (windowsOpen[i].isIdle()){
      windowsOpen[i].increaseIdleTime(1);
      totalWindowIdleTime += 1;

      if (printInfo){
        cout << "Incremented window idle time." << endl;
      }
    }
  }
}

// Checks if it is time to end the simulation
bool RegistrarOffice::endSimulation(){
  // if end of file reached, all windows are idle, and queue is empty
  if (fp->endOfReadFile() && allWindowsIdle() && studentsInLine->isEmpty()){
    return true;

    if (printInfo){
      cout << "End of simulation reached." << endl;
    }
  }
  return false;
}

// Checks if all windows are idle
bool RegistrarOffice::allWindowsIdle(){
  for (int i = 0; i < totalWindowsOpen; ++i){
    if (!windowsOpen[i].isIdle()){
      return false;
    }
  }

  if (printInfo){
    cout << "All windows idle." << endl;
  }

  return true;
}

/*
  The follow are post runtime methods
  They calculate data given data collected in runtime
*/

double RegistrarOffice::getMeanStudentWaitTime(){
  return (static_cast<double>(totalStudentWaitTime) / (double)(1.0 * totalStudentsAttended));
}

double RegistrarOffice::getMedianStudentWaitTime(){
  int tmpArr[totalStudentsAttended];
  double median = -1.0;
  for (int i = 0; i < totalStudentsAttended; ++i){
    Student *hold = processedStudents->removeFront();
    tmpArr[i] = hold->getTimeWaited();
    processedStudents->insertBack(hold);
  }
  // sort array of wait times in ascending order
  for (int i = 0; i < totalStudentsAttended; ++i){
    for (int j = 0; j < totalStudentsAttended; ++j){
      if (tmpArr[i] < tmpArr[j]){
        int tmp = tmpArr[i];
        tmpArr[i] = tmpArr[j];
        tmpArr[j] = tmp;
      }
    }
  }
  if (totalStudentsAttended % 2 == 0){
    int midLeft = tmpArr[totalStudentsAttended / 2 - 1];
    int midRight = tmpArr[totalStudentsAttended / 2];
    median = (static_cast<double>(midLeft) + (double)(1.0 * midRight)) / 2.0;
  }
  else {
    int mid = tmpArr[totalStudentsAttended / 2];
    median = static_cast<double>(mid);
  }
  return median;
}

int RegistrarOffice::getLongestStudentWaitTime(){
  int max = 0;
  for (int i = 0; i < totalStudentsAttended; ++i){
    Student *hold = processedStudents->removeFront();
    if (hold->getTimeWaited() > max){
      max = hold->getTimeWaited();
    }
    processedStudents->insertBack(hold);
  }
  return max;
}

int RegistrarOffice::getNumStudentsWaitingOverTenMins(){
  int num = 0;
  for (int i = 0; i < totalStudentsAttended; ++i){
    Student *hold = processedStudents->removeFront();
    if (hold->getTimeWaited() > 10){
      ++num;
    }
    processedStudents->insertBack(hold);
  }
  return num;
}

double RegistrarOffice::getMeanWindowIdleTime(){
  return (static_cast<double>(totalWindowIdleTime) / (double)(1.0 * totalWindowsOpen));
}

int RegistrarOffice::getLongestWindowIdleTime(){
  int max = 0;
  for (int i = 0; i < totalWindowsOpen; ++i){
    if (windowsOpen[i].getIdleTime() > max){
      max = windowsOpen[i].getIdleTime();
    }
  }
  return max;
}

int RegistrarOffice::getNumWindowsIdleOverFiveMins(){
  int num = 0;
  for (int i = 0; i < totalWindowsOpen; ++i){
    if (windowsOpen[i].getIdleTime() > 5){
      ++num;
    }
  }
  return num;
}

// Output to console data gathered in simulation
void RegistrarOffice::doOutputs(){
  cout << "\nResults for: " << totalStudentsAttended << " total students with " << totalWindowsOpen << " windows open over " << currentTime << " ticks (minutes)." << endl;
  cout << "\nMean student wait time: " << getMeanStudentWaitTime() << endl;
  cout << "Median student wait time: " << getMedianStudentWaitTime() << endl;
  cout << "Longest student wait time: " << getLongestStudentWaitTime() << endl;
  cout << "Number of students waited over ten minutes: " << getNumStudentsWaitingOverTenMins() << endl;
  cout << "\nMean window idle time: " << getMeanWindowIdleTime() << endl;
  cout << "Longest window idle time: " << getLongestWindowIdleTime() << endl;
  cout << "Number of windows idle over five minutes: " << getNumWindowsIdleOverFiveMins() << endl;
}
