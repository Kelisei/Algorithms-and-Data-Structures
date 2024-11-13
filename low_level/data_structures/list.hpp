#ifndef LIST_HPP
#define LIST_HPP

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
#endif