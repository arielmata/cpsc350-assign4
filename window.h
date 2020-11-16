//window.h - header file

// Full name: Ariel Gutierrez
// Student ID: 2318163
// Chapman email: arigutierrez@chapman.edu
// Course number and section: CPSC 350-01
// Assignment or exercise number: Assignment 4

// Assignment 4: A C++ program that simulates and calculate metrics on student
// wait times and window idle times given a specific traffic flow of students.


#include "student.h"

class Window{
public:
  Window();
  ~Window();

  bool isOpen();
  unsigned int getTimeIdle();

  void setIsOpen(bool b);
  void addTimeIdle();
  void addStudent(Student s);
  void addStudentTime();

  unsigned int getStudentWindowTime();
  unsigned int getStudentTime();
  unsigned int getStudentWaitTime();

private:
  bool isOpen; // True if window is open, o.w. false
  unsigned int timeIdle; // Time that window is idle (no students at window)
  Student *student; // Student at window
};
