#ifndef AVL_TREE_TPP
#define AVL_TREE_TPP

#include "avl_tree.hpp"
template <typename T>
void AVLTree<T>::insert(T data)
{
    if (data == this->data)
    {
        return;
    }
    else if (data < this->data)
    {
        if (this->left == nullptr)
        {
            this->left = new AVLTree<T>(data);
        }
        else
        {
            this->left->insert(data);
        }
    }
    else if (data > this->data)
    {
        if (this->right == nullptr)
        {
            this->right = new AVLTree<T>(data);
        }
        else
        {
            this->right->insert(data);
        }
    }

    this->setHeight(1 + std::max(this->left ? this->left->height : -1,
                                 this->right ? this->right->height : -1));

    if (this->getBalance() > 1 && data < this->left->getData())
    {
        this->rotateRight();
        return;
    }
    if (this->getBalance() < -1 && data > this->right->getData())
    {
        this->rotateLeft();
        return;
    }
    if (this->getBalance() > 1 && data > this->left->getData())
    {
        this->left->rotateLeft();
        this->rotateRight();
        return;
    }
    if (this->getBalance() < -1 && data < this->right->getData())
    {
        this->right->rotateRight();
        this->rotateLeft();
        return;
    }
}

template <typename T>
void AVLTree<T>::rotateRight()
{
    AVLTree<T> *newRoot = this->left;
    this->left = newRoot->right;
    newRoot->right = this;

    this->data = newRoot->data;
    this->left = newRoot->left;
    this->right = newRoot->right;
}

template <typename T>
void AVLTree<T>::rotateLeft()
{
    AVLTree<T> *newRoot = this->right;
    this->right = newRoot->left;
    newRoot->left = this;

    this->data = newRoot->data;
    this->left = newRoot->left;
    this->right = newRoot->right;
}

template <typename T>
int AVLTree<T>::getBalance()
{
    return (this->left ? this->left->height : -1) - (this->right ? this->right->height : -1);
}
template <typename T>
void AVLTree<T>::setHeight(int height)
{
    this->height = height;
}

template <typename T>
int AVLTree<T>::getHeight()
{
    return this->height;
}

template <typename T>
T AVLTree<T>::getData()
{
    return this->data;
}

template <typename T>
void AVLTree<T>::setRight(AVLTree *right)
{
    this->right = right;
}

template <typename T>
void AVLTree<T>::setLeft(AVLTree *left)
{
    this->left = left;
}

template <typename T>
AVLTree<T> *AVLTree<T>::getRight()
{
    return this->right;
}

template <typename T>
AVLTree<T> *AVLTree<T>::getLeft()
{
    return this->left;
}

template <typename T>
void AVLTree<T>::remove(T data)
{
    if (data < this->data)
    {
        if (this->left != nullptr)
        {
            this->left->remove(data);
        }
    }
    else if (data > this->data)
    {
        if (this->right != nullptr)
        {
            this->right->remove(data);
        }
    }
    else
    {
        if (this->left == nullptr && this->right == nullptr)
        {
            delete this;
        }
        else if (this->left == nullptr)
        {
            AVLTree<T> *temp = this;
            this = this->right;
            delete temp;
        }
        else if (this->right == nullptr)
        {
            AVLTree<T> *temp = this;
            this = this->left;
            delete temp;
        }
        else
        {
            AVLTree<T> *temp = this->right;
            while (temp->left != nullptr)
            {
                temp = temp->left;
            }
            this->data = temp->data;
            this->right->remove(temp->data);
        }
    }

    this->setHeight(1 + std::max(this->left ? this->left->height : -1,
                                 this->right ? this->right->height : -1));

    if (this->getBalance() > 1 && this->left->getBalance() >= 0)
    {
        this->rotateRight();
        return;
    }
    if (this->getBalance() < -1 && this->right->getBalance() <= 0)
    {
        this->rotateLeft();
        return;
    }
    if (this->getBalance() > 1 && this->left->getBalance() < 0)
    {
        this->left->rotateLeft();
        this->rotateRight();
        return;
    }
    if (this->getBalance() < -1 && this->right->getBalance() > 0)
    {
        this->right->rotateRight();
        this->rotateLeft();
        return;
    }
};

template <typename T>
bool AVLTree<T>::contains(T data)
{
    if (data == this->data)
    {
        return true;
    }
    else if (data < this->data)
    {
        if (this->left == nullptr)
        {
            return false;
        }
        else
        {
            return this->left->contains(data);
        }
    }
    else if (data > this->data)
    {
        if (this->right == nullptr)
        {
            return false;
        }
        else
        {
            return this->right->contains(data);
        }
    }
    return false;
}

template <typename T>
void AVLTree<T>::set(T newData)
{
    this->data = newData;
}
template <typename T>
void AVLTree<T>::inOrderTraversal(void (*visit)(T data))
{
    if (this->left != nullptr)
    {
        this->left->inOrderTraversal(visit);
    }
    visit(this->data);
    if (this->right != nullptr)
    {
        this->right->inOrderTraversal(visit);
    }
}
template <typename T>
AVLTree<T>::~AVLTree()
{
    delete this->left;
    delete this->right;
}
#endif