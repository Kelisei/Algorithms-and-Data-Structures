#ifndef AVL_TREE_TPP
#define AVL_TREE_TPP

#include "avl_tree.hpp"
template <typename T>
AVLNode<T>::AVLNode(T data) : data(data), height(1), left(nullptr), right(nullptr) {}
template <typename T>
T AVLNode<T>::getData() { return data; }
template <typename T>
AVLNode<T> *AVLNode<T>::getLeft() { return left; }
template <typename T>
AVLNode<T> *AVLNode<T>::getRight() { return right; }
template <typename T>
int AVLNode<T>::getHeight() { return height; }
template <typename T>
void AVLNode<T>::setLeft(AVLNode<T> *left) { this->left = left; }
template <typename T>
void AVLNode<T>::setRight(AVLNode<T> *right) { this->right = right; }
template <typename T>
void AVLNode<T>::setHeight(int height) { this->height = height; }

template <typename T>
AVLTree<T>::AVLTree(T data) : root(new AVLNode<T>(data)) {}
template <typename T>
AVLTree<T>::AVLTree() {}
template <typename T>
void AVLTree<T>::insert(T data) { root = insert(root, data); }
template <typename T>
void AVLTree<T>::remove(T data) { root = remove(root, data); }
template <typename T>
bool AVLTree<T>::contains(T data) { return contains(root, data); }
template <typename T>
void AVLTree<T>::inOrderTraversal(void (*func)(T data)) { inOrderTraversal(root, func); }
template <typename T>
void AVLTree<T>::preOrderTraversal(void (*func)(T data)) { preOrderTraversal(root, func); }
template <typename T>
void AVLTree<T>::postOrderTraversal(void (*func)(T data)) { postOrderTraversal(root, func); }

template <typename T>
AVLNode<T> *AVLTree<T>::insert(AVLNode<T> *node, T data)
{
    // Normal BST insertion
    if (node == nullptr)
    {
        return new AVLNode<T>(data);
    }
    else if (data < node->getData())
    {
        node->setLeft(insert(node->getLeft(), data));
    }
    else if (data > node->getData())
    {
        node->setRight(insert(node->getRight(), data));
    }
    else // We don't allow duplicates
    {
        return node;
    }

    // Update height of this ancestor node
    node->setHeight(1 + std::max(getHeight(node->getLeft()), getHeight(node->getRight())));

    int balance = getBalance(node);
    // Left Left Case
    if (balance > 1 && data < node->getLeft()->getData())
    {
        return rightRotate(node);
    } // Right Right Case
    if (balance < -1 && data > node->getRight()->getData())
    {
        return leftRotate(node);
    } // Left Right Case
    if (balance > 1 && data > node->getLeft()->getData())
    {
        node->setLeft(leftRotate(node->getLeft()));
        return rightRotate(node);
    } // Right Left Case
    if (balance < -1 && data < node->getRight()->getData())
    {
        node->setRight(rightRotate(node->getRight()));
        return leftRotate(node);
    }

    return node;
}
template <typename T>
int AVLTree<T>::getHeight(AVLNode<T> *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return node->getHeight();
}
template <typename T>
int AVLTree<T>::getBalance(AVLNode<T> *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return getHeight(node->getLeft()) - getHeight(node->getRight());
}

template <typename T>
AVLNode<T> *AVLTree<T>::rightRotate(AVLNode<T> *node)
{
    AVLNode<T> *left = node->getLeft();
    AVLNode<T> *leftRightChild = left->getRight();

    left->setRight(node);
    node->setLeft(leftRightChild);

    node->setHeight(1 + std::max(getHeight(node->getLeft()), getHeight(node->getRight())));
    left->setHeight(1 + std::max(getHeight(left->getLeft()), getHeight(left->getRight())));

    return left;
}

template <typename T>
AVLNode<T> *AVLTree<T>::leftRotate(AVLNode<T> *node)
{
    AVLNode<T> *right = node->getRight();
    AVLNode<T> *rightLeftChild = right->getLeft();

    right->setLeft(node);
    node->setRight(rightLeftChild);

    node->setHeight(1 + std::max(getHeight(node->getLeft()), getHeight(node->getRight())));
    right->setHeight(1 + std::max(getHeight(right->getLeft()), getHeight(right->getRight())));

    return right;
}

template <typename T>
bool AVLTree<T>::contains(AVLNode<T> *node, T data)
{
    if (node == nullptr)
    {
        return false;
    }
    if (node->getData() == data)
    {
        return true;
    }
    if (data < node->getData())
    {
        return contains(node->getLeft(), data);
    }
    return contains(node->getRight(), data);
}

template <typename T>
void AVLTree<T>::inOrderTraversal(AVLNode<T> *node, void (*func)(T data))
{
    if (node == nullptr)
    {
        return;
    }
    inOrderTraversal(node->getLeft(), func);
    func(node->getData());
    inOrderTraversal(node->getRight(), func);
}

template <typename T>
void AVLTree<T>::preOrderTraversal(AVLNode<T> *node, void (*func)(T data))
{
    if (node == nullptr)
    {
        return;
    }
    func(node->getData());
    preOrderTraversal(node->getLeft(), func);
    preOrderTraversal(node->getRight(), func);
}

template <typename T>
void AVLTree<T>::postOrderTraversal(AVLNode<T> *node, void (*func)(T data))
{
    if (node == nullptr)
    {
        return;
    }
    postOrderTraversal(node->getLeft(), func);
    postOrderTraversal(node->getRight(), func);
    func(node->getData());
}
#endif