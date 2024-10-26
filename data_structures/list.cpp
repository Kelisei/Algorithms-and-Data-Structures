#include <cstddef>
#include <string>
#include <stdexcept>

template <typename T>
class List
{
public:
  virtual void add(T data) = 0;
  virtual void remove(T data) = 0;
  virtual void insert(T data, int pos) = 0;
  virtual void addAll(T data[]) = 0;
  virtual void removeAll(T data[]) = 0;
  virtual void clear() = 0;
  virtual bool contains(T data) = 0;
  virtual bool isEmpty() = 0;
  virtual int size() const = 0;
  virtual T get(int pos) const = 0;
  virtual void set(T data, int pos) = 0;
  virtual T *toArray() = 0;
  virtual List<T> *subList(int from, int to) = 0;
  virtual int indexOf(T data) = 0;
  virtual int lastIndexOf(T data) = 0;
  virtual bool operator==(const List<T> &list) const = 0;
  virtual std::size_t hashCode() = 0;
  virtual std::string toString() = 0;
  virtual ~List() {};
};

template <typename T>
class Node
{
private:
  T data;
  Node<T> *next;
  Node<T> *previous;

public:
  Node(T data, Node *previous, Node *next)
      : data(data), previous(previous), next(next) {}
  Node *getNext();
  Node *getPrevious();
  T getData();
  T *getDataPointer();
  void setData(T data);
  void setNext(Node<T> *next);
  void setPrevious(Node<T> *previous);
};

template <typename T>
class LinkedList : public List<T>
{
private:
  Node<T> *first;
  Node<T> *last;
  int len;
  void removeNode(Node<T> *node)
  {
    if (node == this->first)
    {
      this->first = node->getNext();
      if (this->first != nullptr)
      {
        this->first->setPrevious(nullptr);
      }
    }
    else if (node == this->last)
    {
      this->last = node->getPrevious();
      if (this->last != nullptr)
      {
        this->last->setNext(nullptr);
      }
    }
    else
    {
      node->getPrevious()->setNext(node->getNext());
      node->getNext()->setPrevious(node->getPrevious());
    }
    delete (node);
    this->len--;
  }

public:
  LinkedList() : first(nullptr), last(nullptr), len(0) {}
  void add(T data) override
  {
    Node<T> *newNode = new Node<T>(data, nullptr, nullptr);
    if (this->first == nullptr)
    {
      this->first = this->last = newNode;
    }
    else
    {
      newNode->setPrevious(this->last);
      this->last->setNext(newNode);
      this->last = newNode;
    }
    this->len++;
  };
  void remove(T data) override
  {
    Node<T> *node = this->first;
    while (node != nullptr && node->getData() != data)
    {
      node = node->getNext();
    }
    if (node != nullptr)
    {
      removeNode(node);
    }
  }

  void insert(T data, int pos) override
  {
    if (pos > this->len || pos < 0 || this->len == 0)
    {
      this->add(data);
      return;
    }
    Node<T> *newNode = new Node<T>(data, nullptr, nullptr);
    Node<T> *actual = this->first;
    for (int i = 0; i < pos; i++)
    {
      actual = actual->getNext();
    }
    Node<T> *previous = actual->getPrevious();
    if (previous != nullptr)
    {
      previous->setNext(newNode);
    }
    newNode->setPrevious(previous);
    newNode->setNext(actual);
    actual->setPrevious(newNode);
    if (pos == 0)
    {
      this->first = newNode;
    }
    this->len++;
  }
  void addAll(T data[]) override
  {
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++)
    {
      this->add(data[i]);
    }
  }
  void removeAll(T data[]) override
  {
    Node<T> *node = this->first;
    while (node != nullptr)
    {
      Node<T> *next = node->getNext();
      for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++)
      {
        if (node->getData() == data[i])
        {
          removeNode(node);
          break;
        }
      }
      node = next;
    }
  }
  void clear() override
  {
    Node<T> *node = this->first;
    while (node != nullptr)
    {
      Node<T> *next = node->getNext();
      delete (node);
      node = next;
    }
    this->first = this->last = nullptr;
    this->len = 0;
  }
  bool contains(T data) override
  {
    Node<T> *node = this->first;
    while (node != nullptr && node->getData() != data)
    {
      node = node->getNext();
    }
    return node != nullptr;
  }
  bool isEmpty() override
  {
    return this->len == 0;
  }
  int size() const override
  {
    return this->len;
  }
  T get(int pos) const override
  {
    if (pos >= this->len || pos < 0)
    {
      throw std::out_of_range("Index out of range");
    }
    Node<T> *node = this->first;
    for (int i = 0; i < pos; i++)
    {
      node = node->getNext();
    }
    return node->getData();
  }
  void set(T data, int pos) override
  {
    if (pos >= this->len || pos < 0)
    {
      throw std::out_of_range("Index out of range");
    }
    Node<T> *node = this->first;
    for (int i = 0; i < pos; i++)
    {
      node = node->getNext();
    }
    node->setData(data);
  }
  T *toArray() override
  {
    T *arr = new T[this->len];
    Node<T> *node = this->first;
    for (int i = 0; i < this->len; i++)
    {
      arr[i] = node->getData();
      node = node->getNext();
    }
    return arr;
  }
  List<T> *subList(int from, int to) override
  {
    if (from >= this->len || from < 0 || to >= this->len || to < 0 || from > to)
    {
      throw std::out_of_range("Index out of range");
    }
    LinkedList<T> *list = new LinkedList<T>();
    Node<T> *node = this->first;
    for (int i = 0; i < from; i++)
    {
      node = node->getNext();
    }
    for (int i = from; i <= to; i++)
    {
      list->add(node->getData());
      node = node->getNext();
    }
    return list;
  }
  int indexOf(T data) override
  {
    Node<T> *node = this->first;
    int i = 0;
    while (node != nullptr && node->getData() != data)
    {
      node = node->getNext();
      i++;
    }
    return node == nullptr ? -1 : i;
  }
  int lastIndexOf(T data) override
  {
    Node<T> *node = this->last;
    int i = this->len - 1;
    while (node != nullptr && node->getData() != data)
    {
      node = node->getPrevious();
      i--;
    }
    return node == nullptr ? -1 : i;
  }
  bool operator==(const List<T> &list) const override
  {
    if (this->len != list.size())
    {
      return false;
    }
    for (int i = 0; i < this->len; i++)
    {
      if (this->get(i) != list.get(i))
      {
        return false;
      }
    }
    return true;
  }
  std::size_t hashCode() override
  {
    std::size_t hash = 0;
    Node<T> *node = this->first;
    while (node != nullptr)
    {
      hash += std::hash<T>()(node->getData());
      node = node->getNext();
    }
    return hash;
  }
  std::string toString() override
  {
    std::string str = "[";
    Node<T> *node = this->first;
    while (node != nullptr)
    {
      str += std::to_string(node->getData());
      if (node->getNext() != nullptr)
      {
        str += ", ";
      }
      node = node->getNext();
    }
    str += "]";
    return str;
  }
  virtual ~LinkedList() noexcept
  {
    Node<T> *node = this->first;
    while (node != nullptr)
    {
      Node<T> *next = node->getNext();
      delete (node);
      node = next;
    }
  }
};