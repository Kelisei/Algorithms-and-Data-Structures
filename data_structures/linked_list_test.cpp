#include <iostream>
#include <gtest/gtest.h>
#include "list.hpp"

TEST(LinkedListTest, TestAdd)
{
    LinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.get(0), 1);
    EXPECT_EQ(list.get(1), 2);
    EXPECT_EQ(list.get(2), 3);
}

TEST(LinkedListTest, TestRemove)
{
    LinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    list.remove(2);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.get(0), 1);
    EXPECT_EQ(list.get(1), 3);
}

TEST(LinkedListTest, TestInsert)
{
    LinkedList<int> list;
    list.add(1);
    list.add(3);
    list.add(4);
    list.insert(1, 1); // Add insert in the second element, move the rest to the right
    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(list.get(0), 1);
    EXPECT_EQ(list.get(1), 1);
    EXPECT_EQ(list.get(2), 3);
    EXPECT_EQ(list.get(3), 4);
}

TEST(LinkedListTest, TestContains)
{
    LinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    EXPECT_TRUE(list.contains(2));
    EXPECT_FALSE(list.contains(4));
}

TEST(LinkedListTest, TestIsEmpty)
{
    LinkedList<int> list;
    EXPECT_TRUE(list.isEmpty());
    list.add(1);
    EXPECT_FALSE(list.isEmpty());
}

TEST(LinkedListTest, TestSize)
{
    LinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    EXPECT_EQ(list.size(), 3);
}

TEST(LinkedListTest, TestClear)
{
    LinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    list.clear();
    EXPECT_TRUE(list.isEmpty());
    EXPECT_EQ(list.size(), 0);
}

TEST(LinkedListTest, TestGet)
{
    LinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    EXPECT_EQ(list.get(0), 1);
    EXPECT_EQ(list.get(1), 2);
    EXPECT_EQ(list.get(2), 3);
}

TEST(LinkedListTest, TestSet)
{
    LinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    list.set(4, 1);
    EXPECT_EQ(list.get(1), 4);
}

TEST(LinkedListTest, TestToArray)
{
    LinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    int *arr = list.toArray();
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    delete[] arr;
}

TEST(LinkedListTest, TestSubList)
{
    LinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    List<int> *sublist = list.subList(1, 2);
    EXPECT_EQ(sublist->size(), 2);
    EXPECT_EQ(sublist->get(0), 2);
    EXPECT_EQ(sublist->get(1), 3);
    delete sublist;
}

TEST(LinkedListTest, TestIndexOf)
{
    LinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    EXPECT_EQ(list.indexOf(2), 1);
    EXPECT_EQ(list.indexOf(4), -1);
}

TEST(LinkedListTest, TestLastIndexOf)
{
    LinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(2);
    EXPECT_EQ(list.lastIndexOf(2), 3);
    EXPECT_EQ(list.lastIndexOf(4), -1);
}

TEST(LinkedListTest, TestEquality)
{
    LinkedList<int> list1;
    list1.add(1);
    list1.add(2);
    list1.add(3);

    LinkedList<int> list2;
    list2.add(1);
    list2.add(2);
    list2.add(3);

    EXPECT_TRUE(list1 == list2);

    list2.add(4);
    EXPECT_FALSE(list1 == list2);
}

TEST(LinkedListTest, TestHashCode)
{
    LinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    std::size_t hash = list.hashCode();
    EXPECT_NE(hash, 0);
}

TEST(LinkedListTest, TestToString)
{
    LinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    EXPECT_EQ(list.toString(), "[1, 2, 3]");
}

TEST(LinkedListTest, TestIterator)
{
    LinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    for(int element : list)
    {
        std::cout << element << std::endl;
    }
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    for (int element : list)
    {
        std::cout << element << std::endl;
    }
}