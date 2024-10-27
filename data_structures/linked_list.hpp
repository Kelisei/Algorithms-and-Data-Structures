#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <cstddef>
#include <string>
#include <stdexcept>
#include "list.hpp"

template <typename T>
class DoublyLinkedNode
{
private:
    T data;
    DoublyLinkedNode<T> *next;
    DoublyLinkedNode<T> *previous;

public:
    DoublyLinkedNode(T data, DoublyLinkedNode *previous, DoublyLinkedNode *next)
        : data(data), previous(previous), next(next) {}

    DoublyLinkedNode *getNext();
    DoublyLinkedNode *getPrevious();
    T getData();
    T *getDataPointer();
    void setData(T data);
    void setNext(DoublyLinkedNode<T> *next);
    void setPrevious(DoublyLinkedNode<T> *previous);
};

template <typename T>
class LinkedList : public List<T>
{
private:
    DoublyLinkedNode<T> *first;
    DoublyLinkedNode<T> *last;
    int len;
    void removeNode(DoublyLinkedNode<T> *node);

public:
    class ListIterator
    {
    public:
        DoublyLinkedNode<T> *node;
        ListIterator(DoublyLinkedNode<T> *start) : node(start) {}

        bool hasNext() const;
        T next();
        int operator*() const;
        ListIterator &operator++();
        bool operator!=(const ListIterator &other) const;
    };

    LinkedList();
    void add(T data) override;
    void remove(T data) override;
    void insert(T data, int pos) override;
    void addAll(T data[]) override;
    void removeAll(T data[]) override;
    void clear() override;
    bool contains(T data) override;
    bool isEmpty() override;
    int size() const override;
    T get(int pos) const override;
    void set(T data, int pos) override;
    T *toArray() override;
    List<T> *subList(int from, int to) override;
    int indexOf(T data) override;
    int lastIndexOf(T data) override;
    bool operator==(const List<T> &list) const override;

    std::size_t hashCode() override;
    std::string toString() override;
    ListIterator begin();
    ListIterator end();
    virtual ~LinkedList() noexcept;
};

#include "linked_list.tpp"
#endif
