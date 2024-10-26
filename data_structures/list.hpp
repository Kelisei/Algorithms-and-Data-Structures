#ifndef LIST_HPP
#define LIST_HPP

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
    void removeNode(Node<T> *node);

public:
    class ListIterator
    {
    public:
        Node<T> *node;
        ListIterator(Node<T> *start) : node(start) {}
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

#include "list.tpp"

#endif // LIST_HPP