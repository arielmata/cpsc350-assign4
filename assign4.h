// assign4.h - header file  (maybe name it as assign3.h)

// Full name: Ariel Gutierrez
// Student ID: 2318163
// Chapman email: arigutierrez@chapman.edu
// Course number and section: CPSC 350-01
// Assignment or exercise number: Assignment 4

// Assignment 4: A C++ program that simulates and calculate metrics on student
// wait times and window idle times given a specific traffic flow of students.

#include "GenQueue.h"
#include "window.h"
#include <algorithm> // sort()
#include <fstream> // open and read files
#include <stdexcept> // invalid_argument exception

class Simulation{
public:
  Simulation(string f);
  ~Simulation();

  void simulate();
  bool openFile();
  void calculateStatistics();
  void printStatistics();
private:
  string file; // Name of the file

  // Statistics
  double mean; // Mean student wait time
  double median; // Median student wait time
  int longestWait; // Longest student wait time
  double numStudents10; // Number of students waiting for over 10 minutes
  double meanIdle; // Mean window idle time
  double longestIdle; // Longest window idle time
  double numWindows5; // Number of windows idle for over 5 minutes
  int time; // Time/clock ticks
  int numStudents; // Total number of students
  int numWindows; // Total number of windows

  GenQueue<Student> *studentQueue;
  Window *windowArr;
  int *studentWaitArr;
};
