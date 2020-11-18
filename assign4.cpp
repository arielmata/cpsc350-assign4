// assign4.cpp - implementation file

// Full name: Ariel Gutierrez
// Student ID: 2318163
// Chapman email: arigutierrez@chapman.edu
// Course number and section: CPSC 350-01
// Assignment or exercise number: Assignment 4

// Assignment 4: A C++ program that simulates and calculate metrics on student
// wait times and window idle times given a specific traffic flow of students.

#include "assign4.h"

Simulation::Simulation(string f){
  file = f;
  mean = 0.0;
  median = 0.0;
  longestWait = 0;
  numStudents10 = 0.0;
  meanIdle = 0.0;
  longestIdle = 0.0;
  numWindows5 = 0;
  time = 0;
  numStudents = 0;
  numWindows = 0;
  studentQueue = new GenQueue<Student>;
}


Simulation::~Simulation(){
  // Delete window and student arrays and studentQueue pointer
  delete []windowArr;
  delete []studentWaitArr;
  delete studentQueue;
}


// Runs the simulation
void Simulation::simulate(){
  int studentsDone = 0;
  studentWaitArr = new int[numStudents];
  bool windowOccupied = false;
  // Make Window objects and add them to windowArr
  windowArr = new Window[numWindows];
  for (int i = 0; i < numWindows; ++i){
    Window window;
    windowArr[i] = window;
  }
  // Loops until studentQueue is empty and all windows are empty
  while (!studentQueue->isEmpty() || windowOccupied){
    windowOccupied = false;
    for (int i = 0; i < numWindows; ++i){
      // Window is not open
      if(!windowArr[i].getIsOpen()){
        windowArr[i].addStudentWindowTime(); // Increment student window time
        // Student is done at window
        if (windowArr[i].getStudentTimeNeeded() == windowArr[i].getStudentWindowTime()){
          windowArr[i].setIsOpen(true); // Close window
          // A student in line
          try{
            if ((studentQueue->peek()).getTimeArrived() <= time){
              studentWaitArr[studentsDone] = time - (studentQueue->peek()).getTimeArrived();
              ++studentsDone;
              windowArr[i].addStudent(studentQueue->dequeue());
              windowArr[i].setIsOpen(false); // Close window for student
            }
          } catch (const EmptyQueueException& e) {/*do nothing */}
        }
      }else{
        // Window is open
        try{
          if ((studentQueue->peek()).getTimeArrived() <= time){
            // Set wait time for Student object and add student to Window object
            studentWaitArr[studentsDone] = time - (studentQueue->peek()).getTimeArrived();
            ++studentsDone;
            windowArr[i].addStudent(studentQueue->dequeue());
            windowArr[i].setIsOpen(false); // Close window for student
          }else{
            windowArr[i].addTimeIdle(); //Increment the time that window is Idle for
          }
        }catch(const EmptyQueueException& e){
          windowArr[i].addTimeIdle();
        }
      }
      if (!windowArr[i].getIsOpen())
        windowOccupied = true;
    }
    ++time; //increment time by 1
  }
  calculateStatistics(); // Compute calculations
  printStatistics(); // Print calculations to standard output
}

// Opens and reads the file, creates Student objects and adds them to
// studentQueue, creates Window object and adds them to windowArr, and
// initializes studentWaitArr. Returns true if file is in correct format
// otherwise returns false.
bool Simulation::openFile(){
  string lineStr = "";
  int lineCount = 1, line = 0, arriveTime = 0;

  ifstream f;
  f.open(file);
  bool isTime = true;
  while (getline(f,lineStr)){

    // Line is empty
    if (lineStr == "")
      continue;

    try{
      line = stoi(lineStr);
    }
    catch(invalid_argument ia){
      cerr << "File is not in the appropriate format." << endl;
      cerr << "Exiting Program." << endl;
      studentWaitArr = new int[1];
      windowArr = new Window[1];
      return false;
    }
    // First line should be number of windows open
    if (lineCount == 1){
      numWindows = line;
    }else{
      // Line has the time arrived
      if (isTime){
        arriveTime = line;
        isTime = false;
      }else{
        // Line has number of students
        int n = line;
        for (int i = 0; i < n; ++i){
          getline(f, lineStr, '\n');
          try{
            line = stoi(lineStr); // Convert lineStr to int value
          }
          catch(invalid_argument ia){
            cerr << "File is not in the appropriate format." << endl;
            cerr << "Exiting Program." << endl;
            studentWaitArr = new int[1];
            windowArr = new Window[1];
            return false;
          }

          // Create Student object and append to Queue
          Student student(arriveTime, line);
          studentQueue->append(student);
          ++lineCount;
          ++numStudents;
        }
        isTime = true;
      }
    }
    ++lineCount;
  }
  f.close();
  return true;
}


// Calculates the statistics of the simulation, including, mean student wait
// time, longest student wait time, number of students waiting over 10 minutes,
// mean window idle time, longest window idle time, number of windows idle for
// over 5 minutes.
void Simulation::calculateStatistics(){
  // Calculating the mean student wait time and calculating the number of
  // students waiting over 10 minutes
  int totalWaitTime = 0;
  int totalStudentsWaiting = 0;
  for(int i = 0; i < numStudents; ++i){
    if (studentWaitArr[i] != 0){
      totalWaitTime += studentWaitArr[i];
      ++totalStudentsWaiting;
    }
    if (studentWaitArr[i] > 10)
      ++numStudents10;
  }
  if (totalStudentsWaiting == 0){
    mean = 0;
  }else{
    mean = double(totalWaitTime)/totalStudentsWaiting;
  }

  // Calculating median student wait time
  sort(studentWaitArr, studentWaitArr + numStudents);

  // totalStudentsWaiting is odd
  if (totalStudentsWaiting%2 == 1){
    median = double(studentWaitArr[numStudents/2 + totalStudentsWaiting/2]);
  }
  // numStudents is even
  else{
    median = (double(studentWaitArr[numStudents/2 + totalStudentsWaiting/2]) +
      double(studentWaitArr[numStudents/2 - 1 + totalStudentsWaiting/2]))/2;
  }

  // Calculating the longest student wait time
  longestWait = studentWaitArr[numStudents - 1];

  // Calculating the mean window idle time, longest window idle time, and
  // number of windows idle for over 5 minutes
  int totalIdleTime = 0;
  for (int i = 0; i < numWindows; ++i){
    totalIdleTime += windowArr[i].getTimeIdle();
    if (longestIdle < windowArr[i].getTimeIdle())
      longestIdle = windowArr[i].getTimeIdle();
    if (windowArr[i].getTimeIdle() > 5)
      ++numWindows5;
  }
  meanIdle = double(totalIdleTime)/numWindows;
}


// Prints out the statistics of the simulation
void Simulation::printStatistics(){
  cout << "1. The mean student wait time: " << mean << endl;
  cout << "2. The median student wait time: " << median << endl;
  cout << "3. The longest student wait time: " << longestWait << endl;
  cout << "4. The number of students waiting over 10 minutes: " << numStudents10
    << endl;
  cout << "5. The mean window idle time: " << meanIdle << endl;
  cout << "6. The longest window idle time: " << longestIdle << endl;
  cout << "7. The number of windows idle for over 5 minutes: " << numWindows5
    << endl;
}
