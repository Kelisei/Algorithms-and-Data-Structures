#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

template <typename T>
class AVLNode
{
private:
    T data;
    AVLNode<T> *left;
    AVLNode<T> *right;
    int height;

public:
    AVLNode(T data);
    T getData();
    AVLNode<T> *getLeft();
    AVLNode<T> *getRight();
    int getHeight();
    void setLeft(AVLNode<T> *left);
    void setRight(AVLNode<T> *right);
    void setHeight(int height);
};

template <typename T>
class AVLTree
{
private:
    AVLNode<T> *root;
    AVLNode<T> *insert(AVLNode<T> *node, T data);
    AVLNode<T> *remove(AVLNode<T> *node, T data);

    AVLNode<T> *rightRotate(AVLNode<T> *node);
    AVLNode<T> *leftRotate(AVLNode<T> *node);

    int getHeight(AVLNode<T> *node);
    int getBalance(AVLNode<T> *node);
    bool contains(AVLNode<T> *node, T data);
    void inOrderTraversal(AVLNode<T> *node, void (*func)(T data));
    void preOrderTraversal(AVLNode<T> *node, void (*func)(T data));
    void postOrderTraversal(AVLNode<T> *node, void (*func)(T data));

public:
    AVLTree(T data);
    AVLTree();
    void insert(T data);
    void remove(T data);
    bool contains(T data);
    void inOrderTraversal(void (*func)(T data));
    void preOrderTraversal(void (*func)(T data));
    void postOrderTraversal(void (*func)(T data));
};

#include "avl_tree.tpp"
#endif