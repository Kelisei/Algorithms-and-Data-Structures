#ifndef QUEUE_TPP
#define QUEUE_TPP
#include "queue.hpp"

template <typename T>
QueueNode<T>::~QueueNode()
{
    if (next != nullptr)
    {
        delete next;
    }
}

template <typename T>
QueueNode<T> *QueueNode<T>::getNext()
{
    return next;
}

template <typename T>
T QueueNode<T>::getData()
{
    return data;
}

template <typename T>
T *QueueNode<T>::getDataPointer()
{
    return &data;
}

template <typename T>
void QueueNode<T>::setData(T data)
{
    this->data = data;
}

template <typename T>
void QueueNode<T>::setNext(QueueNode<T> *next)
{
    this->next = next;
}

template <typename T>
Queue<T>::~Queue()
{
    Queue<T>::clear();
}

template <typename T>
bool Queue<T>::enqueue(T data)
{
    if (maxSize != -1 && size >= maxSize)
    {
        return false;
    }

    QueueNode<T> *newNode = new QueueNode<T>(data, nullptr);
    if (tail == nullptr)
    {
        tail = newNode;
        head = newNode;
    }
    else
    {
        tail->setNext(newNode);
        tail = newNode;
    }
    size++;
    return true;
}

template <typename T>
std::optional<T> Queue<T>::dequeue()
{
    if (head == nullptr)
    {
        return std::nullopt;
    }

    QueueNode<T> *temp = head;
    T data = temp->getData();
    head = head->getNext();
    temp->setNext(nullptr);
    delete temp;
    size--;
    return data;
}

template <typename T>
std::optional<T> Queue<T>::peek()
{
    if (head == nullptr)
    {
        return std::nullopt;
    }

    return head->getData();
}

template <typename T>
bool Queue<T>::isEmpty()
{
    return size == 0;
}

template <typename T>
void Queue<T>::clear()
{
    if (head != nullptr)
    {
        delete head;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

#endif // QUEUE_TPP
