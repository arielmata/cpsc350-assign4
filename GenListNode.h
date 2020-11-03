//Generic List Node for Doubly Linked List - GenListNode.h

template <typename T>
class ListNode{
  public:
    ListNode();
    ListNode(T d);
    ~ListNode();

    int data; //value stored in node
    ListNode *next; //pointer to next node
    ListNode *prev;
};

template <typename T>
ListNode<T>::ListNode(){}

template <typename T>
ListNode<T>::ListNode(T d){
  data = d;
  next = NULL; //when creating a new pointer its pointer points to nobody
  prev = NULL;
}

template <typename T>
ListNode<T>::~ListNode(){
  //i'll let you folks build some character and research this
  delete ListNode;
}
