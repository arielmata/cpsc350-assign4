//Generic List Node for Doubly Linked List - GenListNode.h

// Full name: Ariel Gutierrez
// Student ID: 2318163
// Chapman email: arigutierrez@chapman.edu
// Course number and section: CPSC 350-01
// Assignment or exercise number: Assignment 4

// Assignment 4: A C++ program that simulates and calculate metrics on student
// wait times and window idle times given a specific traffic flow of students.

template <typename T>
class ListNode{
  public:
    ListNode(T d);
    ~ListNode();

    int data; // Value stored in node
    ListNode *next; // Pointer to next node
    ListNode *prev; // Pointer to previous node
};

template <typename T>
ListNode<T>::ListNode(T d){
  data = d;
  next = NULL;
  prev = NULL;
}

template <typename T>
ListNode<T>::~ListNode(){
  delete next;
  delete prev;
}
