#include <iostream>
#include <iterator>
#include <stdexcept>
// The node of a doubly linked list, with a generic data type.
template <typename T> class Node {
private:
  T data;
  Node<T> *next;
  Node<T> *previous;

public:
  Node(T data, Node *previous, Node *next)
      : data(data), previous(previous), next(next) {}
  // Returns the pointer to the next node.
  Node *getNext() { return this->next; }
  // Returns the pointer to the previous node.
  Node *getPrevious() { return this->previous; }
  // Returns the data in the node.
  T getData() { return this->data; }
  // Returns a pointer to the data in the node.
  T *getDataPointer() { return &this->data; }
  // Switches the next node for the one given.
  void setNext(Node<T> *next) { this->next = next; }
  // Switches the previous node for the one give.
  void setPrevious(Node<T> *previous) { this->previous = previous; }
};

// A linked list that contains the first and last elements of the list such that
// you can easily add elements.
template <typename T> class LinkedList {
public:
  LinkedList() : first(nullptr), last(nullptr), len(0) {}
  // Adds the give data at the end of the list. It's a copy of the data.
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
  // Inserts the element at the start (making the current first node the second
  // one). If it's null then it acts like a regular append.
  void insertAtStart(T data) {
    Node<T> *newNode = new Node<T>(data, nullptr, nullptr);
    if (this->first == nullptr) {
      this->append(data);
    } else {
      newNode->setNext(this->first);
      this->first = newNode;
    }
    this->len++;
  }
  // Inserts at the given position. If the given index is invalid (> len or <
  // 0) or the list doesn't have elements, then it works like a regular append.
  void insertAt(T data, int pos) {
    if (pos > this->len || pos < 0 || this->len == 0) {
      this->append(data);
      return;
    }
    Node<T> *newNode = new Node<T>(data, nullptr, nullptr);
    Node<T> *actual = this->first;
    for (int i = 0; i < pos; i++) {
      actual = actual->getNext();
    }
    Node<T> *next = actual->getNext();
    if (next != nullptr) {
      next->setPrevious(newNode);
    }
    newNode->setNext(next);
    newNode->setPrevious(actual);
    actual->setNext(newNode);
    this->len++;
  }

  // Returns the first NODE in the list.
  Node<T> *getFirst() { return this->first; }
  // Returns the last NODE in the list.
  Node<T> *getLast() { return this->last; }
  // Returns the lenght of the list.
  int getLen() { return this->len; }
  // Returns the the data of the last elementof the list withour deleting it.
  T peek() { return this->last->getData(); }
  // This function gets the data from the last element in the list and returns
  // it after freeing the node pointer. This can throw a out of range
  // exception if the list is empty.
  T deleteLast() {
    if (this->last == nullptr) {
      throw std::out_of_range("List is empty");
    }
    T data = this->last->getData();
    this->last = this->last->getPrevious();
    if (this->last != nullptr) {
      delete this->last->getNext();
      this->last->setNext(nullptr);
    } else {
      delete this->last;
      this->first = this->last = nullptr;
    }
    this->len--;
    return data;
  }
  // This function gets the data from the first element in the list and
  // returns it after freeing the node pointer. This can throw a out of range
  // exception if the list is empty.
  T deleteFirst() {
    if (this->first == nullptr) {
      throw std::out_of_range("List is empty");
    }
    T data = this->first->getData();
    this->first = this->first->getNext();
    if (this->last != nullptr) {
      delete this->first->getPrevious();
      this->first->setPrevious(nullptr);
    } else {
      delete this->first;
      this->first = this->last = nullptr;
    }
    this->len--;
    return data;
  }
  // Finds the first instance of the data given as parameter, and then deletes
  // the node.
  bool deleteFirstInstance(T data) {
    bool found = false;
    Node<T> *actual = this->first;
    while (found != true && actual != nullptr) {
      if (actual->getData() == data) {
        found = true;
      } else {
        actual = actual->getNext();
      }
    }
    if (found) {
      this->deleteNode(actual);
    }
    return found;
  }
  // This will delete the node off the list and check if it's the first or
  // last element and act accordingly, don't use this with nodes of other
  // lists since it will change the size of this list, use isInList() before
  // or be careful. O(1).
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
  // Recursively finds out if the node is in the list searchf from the first
  // element.
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
  intList.append(1);
  intList.append(2);
  intList.append(3);
  std::cout << "It's deleted?:" << intList.deleteFirstInstance(2) << "\n";

  return 0;
}
