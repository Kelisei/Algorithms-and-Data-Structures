#include <iostream>
#include <gtest/gtest.h>
#include "avl_tree.hpp"

TEST(AVLTest, AVLInsertionTest)
{
    AVLTree<int> tree = AVLTree<int>(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    ASSERT_TRUE(tree.contains(10));
    ASSERT_TRUE(tree.contains(20));
    ASSERT_TRUE(tree.contains(30));
    ASSERT_TRUE(tree.contains(40));
    ASSERT_TRUE(tree.contains(50));
    ASSERT_TRUE(tree.contains(25));
    tree.inOrderTraversal([](int data)
                          { std::cout << data << " "; });
}

TEST(AVLTest, AVLRemovalTest)
{
    AVLTree<int> tree = AVLTree<int>(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    tree.remove(20);
    tree.remove(30);
    tree.remove(40);
    tree.remove(50);
    tree.remove(25);

    ASSERT_TRUE(tree.contains(10));
    ASSERT_FALSE(tree.contains(20));
    ASSERT_FALSE(tree.contains(30));
    ASSERT_FALSE(tree.contains(40));
    ASSERT_FALSE(tree.contains(50));
    ASSERT_FALSE(tree.contains(25));
    tree.inOrderTraversal([](int data)
                          { std::cout << data << " "; });
}