#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cstddef>
#include <optional>

template <typename T>
class QueueNode
{
private:
    QueueNode *next;
    T data;

public:
    QueueNode(T data, QueueNode *next)
        : data(data), next(next) {};
    ~QueueNode();
    QueueNode *getNext();
    T getData();
    T *getDataPointer();
    void setData(T data);
    void setNext(QueueNode<T> *next);
};

template <typename T>
class Queue
{
private:
    QueueNode *tail;
    QueueNode *head;
    size_t size;
    size_t maxSize;

public:
    Queue(size_t maxSize) : tail(nullptr), head(nullptr), size(nullptr), maxSize(maxSize) {};
    Queue() : tail(nullptr), head(nullptr), size(nullptr), maxSize(-1);
    ~Queue();
    bool enqueue(T data);
    bool isEmpty();
    void clear();
    std::optional<T> dequeue();
    std::optional<T> peek(); 
};

#include "queue.tpp"
#endif // QUEUE_HPP
