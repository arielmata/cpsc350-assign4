//header - EmptyDoublyException.h

// Full name: Ariel Gutierrez
// Student ID: 2318163
// Chapman email: arigutierrez@chapman.edu
// Course number and section: CPSC 350-01
// Assignment or exercise number: Assignment 4

// Assignment 4: A C++ program that simulates and calculate metrics on student
// wait times and window idle times given a specific traffic flow of students.


#include <stdexcept>
using namespace std;

//EmptyDoublyException: Exception for throwing an error when stack is empty
class EmptyDoublyException : public runtime_error{
  public:
    EmptyDoublyException(const char* message) : runtime_error(message){}
};
