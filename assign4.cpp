//simulation.cpp - implementation file

// Full name: Ariel Gutierrez
// Student ID: 2318163
// Chapman email: arigutierrez@chapman.edu
// Course number and section: CPSC 350-01
// Assignment or exercise number: Assignment 4

// Assignment 4: A C++ program that simulates and calculate metrics on student
// wait times and window idle times given a specific traffic flow of students.

#include "student.h"
#include "window.h"
#include "simulation.h"
#include <stdexcept> // invalid_argument exception

Simulation::Simulation(string f){
  file = f;
  mean = 0.0;
  median = 0.0;
  longestWait = 0;
  numStudents10 = 0.0;
  meanIdle = 0.0;
  longestIdle = 0.0;
  numWindows5 = 0;
  numIdle = 0.0;
  time = 0;
  numStudents = 0;
  DoublyLinkedList<Student> *studentQueue;
}


Simulation::~Simulation(){
  // Delete window and student arrays and studentQueue pointer
  delete[] windowArr;
  delete[] studentWaitArr;
  delete studentQueue;
}


// Runs the simulation
void Simulation::simulate(){
  int StudentsDone = 0;
  bool allWindowsEmpty = true;

  // Loops until studentQueue is empty and all windows are empty
  while (studentQueue->isEmpty() && allWindowsEmpty){
    allWindowsEmpty = true; // Assume all windows are empty

    for (int i = 0; i < windowArr.size(); ++i){
      windowArr[i]->addTimeIdle(); // Window is open so increment idle time

      // Window is open
      if (window[i]->isOpen()){
        // Student is in queue
        if ((studentQueue->peek())->getTimeArrived() >= time){
          // Set wait time for Student object and add student to Window object
          (studentQueue->peek())->setWaitTime(time - getTimeArrived());
          windowArr[i]->addStudent(studentQueue->dequeue());
          windowArr[i]->setIsOpen(false); // Close window for student
          allWindowsEmpty = false;
        }
        windowArr[i]->addTimeIdle();
      }
      // Window is closed/Student is at window
      else{
        allWindowsEmpty = false;
        windowArr[i]->addStudentWindowTime(); // Increment student window time
        // Student is done at window
        if (windowArr[i]->getStudentTime() ==
          windowArr[i]->getStudentWindowTime()){
          // Set window to closed and add wait time to studentWaitArr
          windowArr[i]->setIsOpen(true);
          studentWaitArr[StudentsDone++] = windowArr[i]->getStudentWaitTime();
        }
      }
    }
    ++time;
  }

  calculateStatistics(); // Compute calculations
  printStatistics(); // Print calculations to standard output
}

// Opens and reads the file, creates Student objects and adds them to
// studentQueue, creates Window object and adds them to windowArr, and
// initializes studentWaitArr.
void Simulation::openFile(){
  string lineStr;
  int lineCount = 1;
  int line;
  int arriveTime;

  ifstream f;
  f.open(file);
  while (getline(f,lineStr)){
    bool isTime = true;

    lineStr.erase(lineStr.length()-1); // Delete new line char

    try{
      line = stoi(lineStr);
    }
    catch(invalid_argument ia){
      cerr << "Invalid argument: " << ia.what() << endl;
    }

    // First line should be number of windows open
    if (lineCount == 1){
      windowArr = new Window*[line];

      // Make Window objects and add them to windowArr
      for (int i = 0; i < line; ++i){
        Window *window = new Window();
        windowArr[i] = window;
      }
    }
    else{
      // Line has the time arrived
      if (isTime){
        arriveTime = line;
        isTime = false;
      }
      // Line has number of students
      else{
        int n = line;
        for (int i = 0; i < n; ++i){
          getline(f, lineStr);
          try{
            line = stoi(lineStr); // Convert lineStr to int value
          }
          catch(invalid_argument ia){
            cerr << "Invalid argument: " << ia.what() << endl;
          }

          // Create Student object and append to Queue
          Student *student = new Student(arriveTime, line);
          studentQueue->append(student);
          ++numStudents;
          ++lineCount;
        }
        isTime = true;
      }
    }
    ++lineCount;
  }
  studentWaitArr = new int*[numStudents];
  f.close();
}


// Calculates the statistics of the simulation, including, mean student wait
// time, longest student wait time, number of students waiting over 10 minutes,
// mean window idle time, longest window idle time, number of windows idle for
// over 5 minutes.
void Simulation::calculateStatistics(){
  // Calculating the mean student wait time and calculating the number of
  // students waiting over 10 minutes
  int totalWaitTime = 0;
  for(int i = 0; i < numStudents; ++i){
    totalWaitTime += studentWaitArr[i];
    if (studentWait[i] > 10)
      ++numStudents10;
  }
  mean = double(totalWaitTime)/numStudents;

  // Calculating median student wait time
  sort(studentWaitArr, studentWaitArr + numStudents);
  // numStudents is odd
  if (numStudents%2 == 1){
    median = studentWaitArr[9/2];
  }
  // numStudents is even
  else{
    median = double(studentWaitArr[numStudents/2] +
      studentWaitArr[numStudents/2 - 1])/2;
  }

  // Calculating the longest student wait time
  longestWait = studentWaitArr[-1];

  // Calculating the mean window idle time, longest window idle time, and
  // number of windows idle for over 5 minutes
  int totalIdleTime = 0;
  for (int i = 0; i < windowArr.size(); ++i){
    totalIdleTime += windowArr[i]->getTimeIdle();
    if (longestIdle < windowArr[i]->getTimeIdle())
      longestIdle = windowArr[i]->getTimeIdle();
    if (windowArr[i]->getTimeIdle() > 5)
      ++numWindows5;
  }
  meanIdle = double(totalIdleTime)/windowArr.size();
}


// Prints out the statistics of the simulation
void Simulation::printStatistics(){
  cout << "Mean student wait time: " << mean << " minutes" << endl;
  cout << "Median student wait time: " << median << " minutes" << endl;
  cout << "Longest student wait time: " << longestWait << " minutes" << endl;
  cout << "Number of students waiting over 10 minutes: " << numStudents10
    << " students" << endl;
  cout << "Mean window idle time: " << meanIdle << " minutes" << endl;
  cout << "Longest window idle time: " << longestIdle << " minutes" << endl;
  cout << "Number of windows idle for over 5 minutes: " << numWindows5
    << " windows" << endl;
}
