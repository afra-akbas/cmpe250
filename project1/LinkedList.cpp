
#include "LinkedList.h"

LinkedList:: LinkedList(){
    this->head = NULL;
    this->tail = NULL;
    length = 0;
}

LinkedList::LinkedList(const LinkedList &list) {
    length = list.length;
    head = list.head;
    tail = list.tail;
}

LinkedList& LinkedList::operator=(const LinkedList &list) {
    length = list.length;
    head = list.head;
    tail = list.tail;
    return *this;
}

//it creates a new node whose data is parameter_data
//if head is null it pushes to the head
//else to the tail thwn increments the length

void LinkedList::pushTail(Member data) {
    Node *n = new Node(data);
    if(!this->head){
        this->head = n;
        this->tail = head;
    }
    else{
        this->tail->next = n;
        this->tail = n;
    }
    length++;
}

LinkedList::~LinkedList() {
    delete head;

}
