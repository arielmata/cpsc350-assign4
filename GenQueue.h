//Generic Queue - GenQueue.h

// Full name: Ariel Gutierrez
// Student ID: 2318163
// Chapman email: arigutierrez@chapman.edu
// Course number and section: CPSC 350-01
// Assignment or exercise number: Assignment 4

// Assignment 4: A C++ program that simulates and calculate metrics on student
// wait times and window idle times given a specific traffic flow of students.

#include "DoublyLinkedList.h"
#include "EmptyQueueException.h"

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
    int getSize();
  private:
    DoublyLinkedList<T> *myQueue;
    int size;
};

// Implentation of GenQueue

template <typename T>
GenQueue<T>::GenQueue(){
  myQueue = new DoublyLinkedList<T>;
  size = 0;
}

template <typename T>
GenQueue<T>::~GenQueue(){
  delete myQueue;
}

template <typename T>
void GenQueue<T>::append(T d){
  myQueue->insertBack(d);
  ++size;
}

template <typename T>
T GenQueue<T>::dequeue(){
  // Queue is empty
  if(isEmpty()){
    //throw excepetion
    throw EmptyQueueException("Queue is empty.");
  }
  else{
    --size;
    return (myQueue->removeFront());
  }
}


template <typename T>
T GenQueue<T>::peek(){
  // Queue is empty
  if(isEmpty()){
    //throw excepetion
    throw EmptyQueueException("Queue is empty.");
  }
  else{
    return myQueue->getFront();
  }
}

template <typename T>
bool GenQueue<T>::isEmpty(){
  return myQueue->isEmpty();
}

template <typename T>
int GenQueue<T>::getSize(){
  return myQueue->getSize();
}
