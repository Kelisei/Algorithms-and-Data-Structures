#ifndef LIST_TPP
#define LIST_TPP

#include "list.hpp"

// Node class member function definitions
template <typename T>
Node<T> *Node<T>::getNext()
{
    return this->next;
}

template <typename T>
Node<T> *Node<T>::getPrevious()
{
    return this->previous;
}

template <typename T>
T Node<T>::getData()
{
    return this->data;
}

template <typename T>
T *Node<T>::getDataPointer()
{
    return &(this->data);
}

template <typename T>
void Node<T>::setData(T data)
{
    this->data = data;
}

template <typename T>
void Node<T>::setNext(Node<T> *next)
{
    this->next = next;
}

template <typename T>
void Node<T>::setPrevious(Node<T> *previous)
{
    this->previous = previous;
}


template <typename T>
LinkedList<T>::LinkedList() : first(nullptr), last(nullptr), len(0) {}

template <typename T>
void LinkedList<T>::add(T data)
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
}

template <typename T>
void LinkedList<T>::remove(T data)
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
template <typename T>
void LinkedList<T>::removeNode(Node<T> *node)
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
        Node<T> *prev = node->getPrevious();
        Node<T> *next = node->getNext();
        if (prev != nullptr)
        {
            prev->setNext(next);
        }
        if (next != nullptr)
        {
            next->setPrevious(prev);
        }
    }
    delete node;
    this->len--;
}

template <typename T>
void LinkedList<T>::insert(T data, int pos)
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

template <typename T>
void LinkedList<T>::addAll(T data[])
{
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++)
    {
        this->add(data[i]);
    }
}

template <typename T>
void LinkedList<T>::removeAll(T data[])
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

template <typename T>
void LinkedList<T>::clear()
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

template <typename T>
bool LinkedList<T>::contains(T data)
{
    Node<T> *node = this->first;
    while (node != nullptr && node->getData() != data)
    {
        node = node->getNext();
    }
    return node != nullptr;
}

template <typename T>
bool LinkedList<T>::isEmpty()
{
    return this->len == 0;
}

template <typename T>
int LinkedList<T>::size() const
{
    return this->len;
}

template <typename T>
T LinkedList<T>::get(int pos) const
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

template <typename T>
void LinkedList<T>::set(T data, int pos)
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

template <typename T>
T *LinkedList<T>::toArray()
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

template <typename T>
List<T> *LinkedList<T>::subList(int from, int to)
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

template <typename T>
int LinkedList<T>::indexOf(T data)
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

template <typename T>
int LinkedList<T>::lastIndexOf(T data)
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

template <typename T>
bool LinkedList<T>::operator==(const List<T> &list) const
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

template <typename T>
std::size_t LinkedList<T>::hashCode()
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

template <typename T>
std::string LinkedList<T>::toString()
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

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::begin()
{
    return Iterator(this->first);
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end()
{
    return Iterator(nullptr);
}

template <typename T>
LinkedList<T>::~LinkedList() noexcept
{
    Node<T> *node = this->first;
    while (node != nullptr)
    {
        Node<T> *next = node->getNext();
        delete (node);
        node = next;
    }
}

#endif // LIST_TPP