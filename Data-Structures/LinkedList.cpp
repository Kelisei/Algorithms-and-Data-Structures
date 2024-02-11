#include <iostream>
// The node of a double linked list, with a generic data type.
template <typename T> class Node {
private:
  T data;
  Node *next;
  Node *previous;

public:
  Node(T data, Node *previous, Node *next)
      : data(data), previous(previous), next(next) {}
  Node *getNext() { return this->next; }
  Node *getPrevious() { return this->previous; }
  T getData() { return this->data; }
  T *getDataPointer() { return &this->data; }
  void setNext(Node<T> *next) { this->next = next; }
  void setPrevious(Node<T> *previous) { this->previous = previous; }
};

// A linked list that contains the first and last elements of the list such that
// you can easily add elements.
template <typename T> class LinkedList {
public:
  LinkedList() : first(nullptr), last(nullptr) {}
  void append(T data) {
    if (this->first == nullptr) {
      this->first = new Node<T>(data, nullptr, nullptr);
      this->last = first;
    } else {
      Node<T> *newNode = new Node<T>(data, nullptr, nullptr);
      this->last->setNext(newNode);
      newNode->setPrevious(this->last);
      this->last = newNode;
    }
  }
  Node<T> *getFirst() { return this->first; }

private:
  Node<T> *first;
  Node<T> *last;
};

int main() {
  LinkedList<int> intList;
  intList.append(1);
  intList.append(2);
  intList.append(3);
  intList.append(4);

  Node<int> *current = intList.getFirst();
  while (current != nullptr) {
    std::cout << current->getData() << "\n";
    current = current->getNext();
  }
  return 0;
}
