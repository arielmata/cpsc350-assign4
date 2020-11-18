// Student.cpp - implementation file

// Full name: Ariel Gutierrez
// Student ID: 2318163
// Chapman email: arigutierrez@chapman.edu
// Course number and section: CPSC 350-01
// Assignment or exercise number: Assignment 4

// Assignment 4: A C++ program that simulates and calculate metrics on student
// wait times and window idle times given a specific traffic flow of students.

#include "student.h"

Student::Student(){
  timeArrived = 0;
  timeNeeded = 0;
  waitTime = 0;
  windowTime = 0;
}

Student::Student(int t, int tn){
  timeArrived = t;
  timeNeeded = tn;
  waitTime = 0;
  windowTime = 0;
}

Student::~Student(){}

// Sets wait time to input int wt
void Student::setWaitTime(int wt){
  waitTime = wt;
}


// Increments windowTime by one
void Student::addWindowTime(){
  ++windowTime;
}


// Returns timeArrived
int Student::getTimeArrived(){
  return timeArrived;
}

//Returns timeNeeded
int Student::getTimeNeeded(){
  return timeNeeded;
}

// Returns waitTime
int Student::getWaitTime(){
  return waitTime;
}

// Returns windowTime
int Student::getWindowTime(){
  return windowTime;
}
