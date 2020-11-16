//Generic Queue - GenQueue.h
/*
Full name: Ariel Gutierrez
Student ID: 2318163
Chapman email: arigutierrez@chapman.edu
Course number and section: CPSC 350-01
Assignment or exercise number: Assignment 4

Assignment 4: A C++ program that simulates and calculate metrics on student wait
times and window idle times given a specific traffic flow of students.
*/
#include <iostream>

using namespace std;

template <typename T>
class GenQueue{
  public:
    GenQueue(); // Default constructor
    ~GenQueue(); // Destructor

    // Core functions
    void append(T d); // enqueue
    T dequeue(); // dequeue
    T peek();

    // Aux functions
    bool isEmpty();
    unsigned int getSize();
  private:
    DoublyLinkedList<T> *myQueue;
};

// Implentation of GenQueue

template <typename T>
GenQueue<T>::GenQueue(){
  myQueue = new DoublyLinkedList();
  front = 0;
  rear = 0;
  size = 0;
}

template <typename T>
GenQueue<T>::~GenQueue(){
  delete myQueue;
}

template <typename T>
void GenQueue<T>::append(T d){
  myQueue->append(d);
  ++size;
}

template <typename T>
T GenQueue<T>::dequeue(){
  // Queue is empty
  if(isEmpty()){
    cout << "Queue is empty" << endl; //throw queue is empty exception
    //NOT DONE
    return NULL;
  }

  --size;
  return (myQueue->removeFront());
}

template <typename T>
unsigned int GenQueue<T>::size(){
  return size;
}

template <typename T>
T GenQueue<T>::peek(){
  // Queue is empty
  if(isEmpty()){
    cout << "Queue is empty" << endl; //throw queue is empty exception
    //NOT DONE
    return NULL;
  }

  return myQueue->getFront();
}

template <typename T>
bool GenQueue<T>::isEmpty(){
  return GenQueue->isEmpty();
}

template <typename T>
unsigned int GenQueue<T>::getSize(){
  return myQueue->getSize();
}
