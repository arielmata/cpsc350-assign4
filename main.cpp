// main.cpp - main file

// Full name: Ariel Gutierrez
// Student ID: 2318163
// Chapman email: arigutierrez@chapman.edu
// Course number and section: CPSC 350-01
// Assignment or exercise number: Assignment 4

// Assignment 4: A C++ program that simulates and calculate metrics on student
// wait times and window idle times given a specific traffic flow of students.


#include "assign4.h"

int main(int argc, char **argv){
  string file;
  // No command line arguments were given
  if(argc < 2){
    cout << "No file was given. Please try again." << endl;
    cout << "Exiting Program." << endl;
    return 0;
  }
  // More than one command line argument was given
  else if(argc > 2){
    cout << "More than one file was given. Please try again." << endl;
    cout << "Exiting Program." << endl;
    return 0;
  }
  // Command line argument is found
  else{
    file = argv[1];
    ifstream infile;
    infile.open(file);
    // Can't open the file so close it
    if(infile.fail()){
      cout << "The file is not accessible." << endl;
      cout << "Exiting program." << endl;
      infile.close();
      return 0;
    }
    infile.close();
  }

  Simulation *s = new Simulation(file); // Create instance of Simulate

  // There is a problem with the format of the file
  if(!s->openFile()){
    delete s;
    return 0;
  }

  s->simulate(); // Run simulation
  delete s;
  return 0;
}
