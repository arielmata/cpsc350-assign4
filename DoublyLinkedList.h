//Generic Doubly Linked List - DoublyLinkedList.h

// Full name: Ariel Gutierrez
// Student ID: 2318163
// Chapman email: arigutierrez@chapman.edu
// Course number and section: CPSC 350-01
// Assignment or exercise number: Assignment 4

// Assignment 4: A C++ program that simulates and calculate metrics on student
// wait times and window idle times given a specific traffic flow of students.

#include "GenListNode.h"
#include <iostream>

template <typename T>
class DoublyLinkedList{
  public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void insertFront(T d);
    void insertBack(T d);
    void insertAfter(GenListNode *curr, T d);
    T removeFront();
    T removeBack();
    int find(T value); // AKA search()
    T deletePos(int pos);
    T removeNode(T key); // Key represents the value we are going to search for and delete

    void printList();
    bool isEmpty();
    unsigned int getSize();
    T getFront();
    T getBack();
    void ListInsertionSortDoublyLinked();
  private:
    ListNode *front;
    ListNode *back;
    unsigned int size;
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(){
  // Start with an empty doubly linked list
  front = NULL;
  back = NULL;
  size = 0;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList(){
  delete front;
  delete back;
}

template <typename T>
void DoublyLinkedList<T>::insertFront(T d){
  GenListNode *node = new GenListNode<T>(d);

  if(size == 0){
    back = node;
  }else{
    front->prev = node;
    node->next = front;
  }
  front = node;
  ++size;
}

template <typename T>
void DoublyLinkedList<T>::insertBack(T d){
  GenListNode *node = new GenListNode<T>(d);

  if(front == NULL){
    front = node;
  }else{
    back->next = node;
    node->prev = back;
  }
  back = node;
  ++size;
}

template <typename T>
void DoublyLinkedList<T>::insertAfter(GenListNode *curr, T d){
  GenListNode *node = new GenListNode<T>(d);

  if(front == NULL){
    front = node;
    back = node;
  }else if (curr == back){
    back->next = node;
    node->prev = back;
    back = node;
  }else{
    GenListNode *suc = curr->next;
    node->next = suc;
    node->prev = curr;
    curr->next = node;
    suc->prev = node;
  }
}

template <typename T>
T DoublyLinkedList<T>::removeFront(){
  GenListNode *node = front;

  if(isEmpty()){
    return NULL;
  }

  if(front->next == NULL){
    back = NULL;
  }else{
    front->next->prev = NULL;
  }
  front = front->next;
  --size;
  node->next = NULL;
  T temp = node->data;

  delete node;
  return temp;
}

template <typename T>
T DoublyLinkedList<T>::removeBack(){
  GenListNode *node = back;
  if(isEmpty()){
    //IDK WHAT TO DO
    return NULL;
  }

  if(back->prev == NULL){
    front == NULL;
  }else{
    back->prev->next = NULL;
  }
  back = node->prev;
  --size;
  node->prev = NULL;
  T temp = node->data;

  delete node;
  return temp;
}

template <typename T>
int DoublyLinkedList<T>::find(T value){
  int pos = -1;
  GenListNode *curr = front;

  while(curr != NULL){
    ++pos;
    if(value = curr->data)
      break;
    curr = curr->next;
  }
  // Did not find value
  if(curr == NULL)
    pos = -1;

  return pos;
}

template <typename T>
T DoublyLinkedList<T>::removeNode(T key){
  GenListNode *curr = front;

  //Loop through list to find the key/value
  while(curr->data != key){
    curr = curr->next;

    if(curr == NULL)
      return NULL;
  }

  //now if we get here, we found it, let's proceed to delete

  // Let's start with the front
  if(curr == front){
    front = curr->next;
    front->prev = NULL;
  }else if(curr == back){
    back = curr->prev;
    back->next = NULL;
  }else{
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
  }

  curr->prev = NULL;
  curr->next = NULL;
  --size;
  T temp = curr->data;
  delete curr;

  return temp;
}

/*
int DoublyLinkedList<T>::deletePos(int pos){
  int p = 0;
  ListNode *curr = front;
  ListNode *prev = front;
  //erorr check if pos is not negative
  while(p != pos){
    //iterate and update my pointers
    prev = curr;
    curr = curr->next;
    p++;
  }
  // we found our target, all pointers shoudl be in the correct locations
  prev->next = curr->next;
  curr->next = NULL;
  int temp = curr->data;
  size--;

  delete curr;
  return temp;
}
*/

template <typename T>
void DoublyLinkedList<T>::printList(){
  GenListNode *curr = front;

  while(curr != NULL){
    cout << curr->data << endl;
    curr = curr->next;
  }
  delete curr;
}

template <typename T>
void DoublyLinkedList<T>::printListReverse(){
  GenListNode *curr = back;

  while(curr != NULL){
    cout << curr->data << endl;
    curr = curr->prev;
  }
  delete curr;
}

template <typename T>
bool DoublyLinkedList<T>::isEmpty(){
  return (front == NULL && back == NULL);
}

template <typename T>
unsigned int DoublyLinkedList<T>::getSize(){
  return size;
}

template <typename T>
T DoublyLinkedList<T>::getFront(){
  return front;
}

template <typename T>
T DoublyLinkedList<T>::getBack(){
  return back;
}

template <typename T>
void DoublyLinkedList<T>::InsertionSortDoublyLinked(){
  GenListNode *curr = list->front->next;
  while (curr != NULL){
    GenListNode *nextNode = curr->next;
    GenListNode *searchNode = curr->prev;
    while ((searchNode != NULL) && (searchNode->data > curr->data){
      searchNode = searchNode->prev;
    }

    // Remove and re-insert curr
    removeNode(curr->data);
    if(searchNode == NULL){
      curr->prev = NULL;
      insertFront(curr->data);
    }
    else{
      insertAfter(searchNode, curr->data);
    }
    //advance to next node
    curr = nextNode;
  }
}
