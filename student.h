// Student.h - header file

// Full name: Ariel Gutierrez
// Student ID: 2318163
// Chapman email: arigutierrez@chapman.edu
// Course number and section: CPSC 350-01
// Assignment or exercise number: Assignment 4

// Assignment 4: A C++ program that simulates and calculate metrics on student
// wait times and window idle times given a specific traffic flow of students.

class Student{
public:
  Student(); // Default constructor
  Student(int t, int tn); // Overloaded constructor
  ~Student(); // Destructor

  void setWaitTime(int wt);
  void addWindowTime();

  int getTimeArrived();
  int getTimeNeeded();
  int getWaitTime();
  int getWindowTime();

private:
  int timeArrived; // Time that the student arrived
  int timeNeeded;  // Amount of time that student will stay at window
  int waitTime; // Time that student has waited for in queue
  int windowTime; // Amount of time that student has stayed at window
};
