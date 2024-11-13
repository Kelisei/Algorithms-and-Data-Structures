#ifndef TREE_HPP
#define TREE_HPP


#include <cstddef>

template <typename T>
class Tree {
public:
    virtual ~Tree() {}

    virtual void insert(const T& value) = 0;
    virtual void remove(const T& value) = 0;
    virtual bool contains(const T& value) const = 0;
    virtual void clear() = 0;
    virtual bool isEmpty() const = 0;
    virtual size_t size() const = 0;
};

#endif