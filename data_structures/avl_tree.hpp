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

/**
 * @class AVLTree
 * @brief A self-balancing binary search tree (AVL Tree) implementation.
 * 
 * @tparam T The type of elements stored in the tree.
 * 
 * This class provides an implementation of an AVL Tree, which is a type of 
 * self-balancing binary search tree. It ensures that the tree remains 
 * balanced after insertions and deletions, providing O(log n) time complexity 
 * for these operations.
 * 
 * @note This class inherits from the Tree<T> class.
 */
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
    /*
    * @brief This method inserts a value into the AVL Tree.
    *
    * @param data The value to be inserted.
    */
    void insert(const T &data) override;
    /*
    * @brief This method removes a value from the AVL Tree.
    *
    * @param data The value to be removed.
    */
    void remove(const T &data) override;
    /*
    * @brief This method checks if a value is contained in the AVL Tree.
    *
    * @param data The value to be checked.
    * @return true if the value is contained in the tree, false otherwise.
    */
    bool contains(const T &data) const override; // const añadido
    /*
    * @brief This method clears the AVL Tree, removing all elements.
    */
    void clear() override;
    /*
    * @brief This method checks if the AVL Tree is empty.
    *
    * @return true if the tree is empty, false otherwise.
    */
    bool isEmpty() const override; // const añadido
    /*
    * @brief This method returns the number of elements in the AVL Tree.
    *
    * @return The number of elements in the tree.
    */
    size_t size() const override;  // const añadido
    /*
    * @brief This method performs an in-order traversal of the AVL Tree.
    *
    * @param func A function that will be called for each element in the tree.
    */
    void inOrderTraversal(void (*func)(T data));
    /*
    * @brief This method performs a pre-order traversal of the AVL Tree.
    *
    * @param func A function that will be called for each element in the tree.
    */
    void preOrderTraversal(void (*func)(T data));
    /*
    * @brief This method performs a post-order traversal of the AVL Tree.
    *
    * @param func A function that will be called for each element in the tree.
    */
    void postOrderTraversal(void (*func)(T data));
    ~AVLTree();
};

#include "avl_tree.tpp"
#endif