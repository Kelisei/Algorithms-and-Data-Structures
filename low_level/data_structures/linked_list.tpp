#ifndef LIST_TPP
#define LIST_TPP

#include "linked_list.hpp"

// DoublyLinkedNode class member function definitions
template <typename T>
DoublyLinkedNode<T> *DoublyLinkedNode<T>::getNext()
{
    return this->next;
}

template <typename T>
DoublyLinkedNode<T> *DoublyLinkedNode<T>::getPrevious()
{
    return this->previous;
}

template <typename T>
T DoublyLinkedNode<T>::getData()
{
    return this->data;
}

template <typename T>
T *DoublyLinkedNode<T>::getDataPointer()
{
    return &(this->data);
}

template <typename T>
void DoublyLinkedNode<T>::setData(T data)
{
    this->data = data;
}

template <typename T>
void DoublyLinkedNode<T>::setNext(DoublyLinkedNode<T> *next)
{
    this->next = next;
}

template <typename T>
void DoublyLinkedNode<T>::setPrevious(DoublyLinkedNode<T> *previous)
{
    this->previous = previous;
}


// LinkedList class member function definitions
template <typename T>
bool LinkedList<T>::ListIterator::hasNext() const
{
    return node != nullptr;
};
template <typename T>
T LinkedList<T>::ListIterator::next()
{
    if (!hasNext())
    {
        throw std::out_of_range("No more elements");
    }
    T data = node->getData();
    node = node->getNext();
    return data;
}
template <typename T>
int LinkedList<T>::ListIterator::operator*() const
{
    return node->getData();
}
template <typename T>
typename LinkedList<T>::ListIterator &LinkedList<T>::ListIterator::operator++()
{
    node = node->getNext();
    return *this;
}
template <typename T>
bool LinkedList<T>::ListIterator::operator!=(const ListIterator &other) const
{
    return node != other.node;
}

template <typename T>
LinkedList<T>::LinkedList() : first(nullptr), last(nullptr), len(0) {}

template <typename T>
void LinkedList<T>::add(T data)
{
    DoublyLinkedNode<T> *newNode = new DoublyLinkedNode<T>(data, nullptr, nullptr);
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
    DoublyLinkedNode<T> *node = this->first;
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
void LinkedList<T>::removeNode(DoublyLinkedNode<T> *node)
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
        DoublyLinkedNode<T> *prev = node->getPrevious();
        DoublyLinkedNode<T> *next = node->getNext();
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
    DoublyLinkedNode<T> *newNode = new DoublyLinkedNode<T>(data, nullptr, nullptr);
    DoublyLinkedNode<T> *actual = this->first;
    for (int i = 0; i < pos; i++)
    {
        actual = actual->getNext();
    }
    DoublyLinkedNode<T> *previous = actual->getPrevious();
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
    DoublyLinkedNode<T> *node = this->first;
    while (node != nullptr)
    {
        DoublyLinkedNode<T> *next = node->getNext();
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
    DoublyLinkedNode<T> *node = this->first;
    while (node != nullptr)
    {
        DoublyLinkedNode<T> *next = node->getNext();
        delete (node);
        node = next;
    }
    this->first = this->last = nullptr;
    this->len = 0;
}

template <typename T>
bool LinkedList<T>::contains(T data)
{
    DoublyLinkedNode<T> *node = this->first;
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
    DoublyLinkedNode<T> *node = this->first;
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
    DoublyLinkedNode<T> *node = this->first;
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
    DoublyLinkedNode<T> *node = this->first;
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
    DoublyLinkedNode<T> *node = this->first;
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
    DoublyLinkedNode<T> *node = this->first;
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
    DoublyLinkedNode<T> *node = this->last;
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
    DoublyLinkedNode<T> *node = this->first;
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
    DoublyLinkedNode<T> *node = this->first;
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
typename LinkedList<T>::ListIterator LinkedList<T>::begin()
{
    return ListIterator(this->first);
}

template <typename T>
typename LinkedList<T>::ListIterator LinkedList<T>::end()
{
    return ListIterator(nullptr);
}

template <typename T>
LinkedList<T>::~LinkedList() noexcept
{
    DoublyLinkedNode<T> *node = this->first;
    while (node != nullptr)
    {
        DoublyLinkedNode<T> *next = node->getNext();
        delete (node);
        node = next;
    }
}

#endif // LIST_TPP