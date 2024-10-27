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