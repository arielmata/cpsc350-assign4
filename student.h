//Student.h - header file

// Full name: Ariel Gutierrez
// Student ID: 2318163
// Chapman email: arigutierrez@chapman.edu
// Course number and section: CPSC 350-01
// Assignment or exercise number: Assignment 4

// Assignment 4: A C++ program that simulates and calculate metrics on student
// wait times and window idle times given a specific traffic flow of students.


class Student{
  public:
    Student(unsigned int t, unsigned int tn); // Overloaded constructor
    ~Student(); // Destructor

    void setWaitTime(unsigned int wt);
    void addWindowTime();

    unsigned int getTimeArrived();
    unsigned int getWaitTime();
    unsigned int getWindowTime();
  private:
    unsigned int timeArrived; // Time that the student arrived
    unsigned int waitTime; // Time that student has waited for
    unsigned int windowTime; // Amount of ime that student will stay at window
};
