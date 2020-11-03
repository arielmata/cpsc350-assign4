//Generic Doubly Linked List - DoublyLinkedList.h

template <typename T>
class DoublyLinkedList{
  public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    //core functions
    void insertFront(T d);
    void insertBack(T d);
    T removeFront();
    T removeBack();
    int find(T value); // AKA search()
    //int deletePos(int pos);

    /* new function for double linked list */
    T removeNode(T key); //key represents the value we are going to search for and delete

    //helper functions
    void printList();
    bool isEmpty();
    unsigned int getSize();
  private:
    ListNode *front;
    ListNode *back;
    unsigned int size; //size can't be negative
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(){
  front = NULL;
  back = NULL;
  size = 0;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList(){
  //build some character, research
  delete front;
  delete back;
}

template <typename T>
void DoublyLinkedList<T>::insertFront(T d){
  GenListNode *node = new GenListNode<T>(d);
  //we need to update the back pointer as well
  //what if front and back are the same
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
    front = back;
  }else{
    back->next = node;
    node->prev = back;
  }
  back = node;
  ++size;
}

template <typename T>
T DoublyLinkedList<T>::removeFront(){
  GenListNode *node = front;
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
  //did not find value
  if(curr = NULL)
    pos = -1;

  return pos;
}

template <typename T>
int DoublyLinkedList<T>::removeNode(int key){
  //would we have to use our find function
  ListNode *curr = front;
  //now i need to loop through list to find the key/value
  while(curr->data != key){
    curr = curr->next;

    if(curr == NULL)
      return -1;
  }

  //now if we get here, we found it, let's proceed to delete

  //let's start with the front
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
  int temp = curr->data;
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
  ListNode *curr = front;

  while(curr != NULL){
    cout << curr->data << endl;
    curr = curr->next;
  }
  delete curr;
}

template <typename T>
bool DoublyLinkedList<T>::isEmpty(){

}

template <typename T>
unsigned int DoublyLinkedList<T>::getSize(){
  return size;
}
