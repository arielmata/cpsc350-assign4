// window.cpp - implementation file

// Full name: Ariel Gutierrez
// Student ID: 2318163
// Chapman email: arigutierrez@chapman.edu
// Course number and section: CPSC 350-01
// Assignment or exercise number: Assignment 4

// Assignment 4: A C++ program that simulates and calculate metrics on student
// wait times and window idle times given a specific traffic flow of students.

#include "window.h"

Window::Window(){
  isOpen = true;
  timeIdle = 0;
}

Window::~Window(){}

// Returns true if window is open, otherwise returns false
bool Window::getIsOpen(){
  return isOpen;
}

// Retruns the time for when the window was idle
int Window::getTimeIdle(){
  return timeIdle;
}

// Sets isOpen to either true or false
void Window::setIsOpen(bool b){
  isOpen = b;
}

// Increments one to timeIdle
void Window::addTimeIdle(){
  ++timeIdle;
}

// Adds Student object to student attribute
void Window::addStudent(Student s){
  student = s;
}

// Increments time student was at window by one clock tick
void Window::addStudentWindowTime(){
  student.addWindowTime();
}

// Returns the time student has been at window for
int Window::getStudentWindowTime(){
  return student.getWindowTime();
}

//Returns the time student needs to be at window
int Window::getStudentTimeNeeded(){
  return student.getTimeNeeded();
}
