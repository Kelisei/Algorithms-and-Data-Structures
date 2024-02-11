#include <iostream>
#include <iterator>
#include <stdexcept>
// The node of a double linked list, with a generic data type.
template <typename T> class Node {
private:
  T data;
  Node<T> *next;
  Node<T> *previous;

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
  LinkedList() : first(nullptr), last(nullptr), len(0) {}
  void append(T data) {
    Node<T> *newNode = new Node<T>(data, nullptr, nullptr);
    if (this->first == nullptr) {
      this->first = this->last = newNode;
    } else {
      newNode->setPrevious(this->last);
      this->last->setNext(newNode);
      this->last = newNode;
    }
    this->len++;
  }
  Node<T> *getFirst() { return this->first; }
  Node<T> *getLast() { return this->last; }
  int getLen() { return this->len; }
  T peek() { return this->last->getData(); }
  // This function gets the data from the last element in the list and returns
  // it after freeing the node pointer. This can throw a out of range exception
  // if the list is empty.
  T deleteLast() {
    if (this->last == nullptr) {
      throw std::out_of_range("List is empty");
    }
    T data = this->last->getData();
    this->last = this->last->getPrevious();
    if (last != nullptr) {
      delete this->last->getNext();
      this->last->setNext(nullptr);
    } else {
      delete this->last;
      this->first = this->last = nullptr;
    }
    this->len--;
    return data;
  }
  // This will delete the node off the list and check if it's the first or last
  // element and act accordingly, don't use this with nodes of other lists since
  // I will change the size of this list, use isInList() before or be careful.
  // O(1).
  void deleteNode(Node<T> *node) {
    if (node == nullptr) {
      return;
    }
    if (node == this->first) {
      first = first->getNext();
      delete first->getPrevious();
      first->setPrevious(nullptr);
    } else if (node == this->last) {
      last = last->getPrevious();
      last->setNext(nullptr);
    } else {
      node->getPrevious()->setNext(node->getNext());
      node->getNext()->setPrevious(node->getPrevious());
    }
    delete (node);
    this->len--;
    return;
  }

  bool isInList(Node<T> *node) { return findNode(this->first, node); }

private:
  Node<T> *first;
  Node<T> *last;
  int len;
  bool findNode(Node<T> *actual, Node<T> *node) {
    if (actual == nullptr) {
      return false;
    } else if (actual == node) {
      return true;
    } else {
      return findNode(actual->getNext(), node);
    }
  }
};

int main() {
  LinkedList<int> intList;
  intList.append(1);
  intList.append(2);
  intList.append(3);
  intList.append(4);
  std::cout << intList.peek() << "\n";
  int lenght = intList.getLen();
  std::cout << lenght << "\n";
  for (int i = 0; i < lenght; i++) {
    std::cout << intList.deleteLast() << "\n";
  }
  std::cout << "NEW DEFINITION"
            << "\n";
  intList.append(1);
  std::cout << "add 1"
            << "\n";
  intList.append(2);
  intList.append(3);
  std::cout << intList.peek() << "\n";
  Node<int> *node = intList.getFirst();
  std::cout << "is the first node in list?:" << intList.isInList(node) << "\n";
  node = node->getNext();
  intList.deleteNode(node);
  lenght = intList.getLen();
  for (int i = 0; i < lenght; i++) {
    std::cout << intList.deleteLast() << "\n";
  }
  return 0;
}
