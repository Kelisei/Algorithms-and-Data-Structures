#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include "tree.hpp"
template <typename T>
class AVLNode
{
private:
    T data;
    AVLNode<T> *left;
    AVLNode<T> *right;
    int height;

public:
    AVLNode(const T &data);
    T getData();
    void setData(const T &data);
    AVLNode<T> *getLeft();
    AVLNode<T> *getRight();
    int getHeight();
    void setLeft(AVLNode<T> *left);
    void setRight(AVLNode<T> *right);
    void setHeight(int height);
    ~AVLNode();
};

template <typename T>
class AVLTree : public Tree<T>
{
private:
    AVLNode<T> *root;
    AVLNode<T> *insert(AVLNode<T> *node, T data);
    AVLNode<T> *remove(AVLNode<T> *node, T data);
    void clear(AVLNode<T> *node);
    AVLNode<T> *rightRotate(AVLNode<T> *node);
    AVLNode<T> *leftRotate(AVLNode<T> *node);

    int getHeight(AVLNode<T> *node);
    int getBalance(AVLNode<T> *node);
    bool contains(AVLNode<T> *node, T data) const;
    void inOrderTraversal(AVLNode<T> *node, void (*func)(T data));
    void preOrderTraversal(AVLNode<T> *node, void (*func)(T data));
    void postOrderTraversal(AVLNode<T> *node, void (*func)(T data));
    size_t size(AVLNode<T> *node) const;

public:
    AVLTree(const T &data);
    AVLTree();
    void insert(const T &data) override;
    void remove(const T &data) override;
    bool contains(const T &data) const override; // const añadido
    void clear() override;
    bool isEmpty() const override; // const añadido
    size_t size() const override;  // const añadido
    void inOrderTraversal(void (*func)(T data));
    void preOrderTraversal(void (*func)(T data));
    void postOrderTraversal(void (*func)(T data));
    ~AVLTree();
};

#include "avl_tree.tpp"
#endif