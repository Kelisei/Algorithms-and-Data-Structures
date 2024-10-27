#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

template <typename T>
class AVLTree
{
private:
    AVLTree *left;
    AVLTree *right;

    T data;
    int height;

public:
    void rotateRight();
    void rotateLeft();
    AVLTree(T data) : left(nullptr), right(nullptr), height(0), data(data) {}

    T getData();

    void setLeft(AVLTree *left);
    void setRight(AVLTree *right);

    AVLTree *getLeft();
    AVLTree *getRight();

    void insert(T data);
    void remove(T data);
    bool contains(T data);
    void set(T newData);

    void setHeight(int height);
    int getHeight();
    int getBalance();

    void inOrderTraversal(void (*visit)(T data));
    /*void preOrderTraversal(void (*visit)(T data));
    void postOrderTraversal(void (*visit)(T data));
    void levelOrderTraversal(void (*visit)(T data));
    */
    ~AVLTree();
};
#include "avl_tree.tpp"
#endif