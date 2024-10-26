#include <gtest/gtest.h>

#include "algorithms.hpp"

TEST(AlgorithmsTest, InsertionSortTest) {
  int array[] = {5, 2, 9, 1, 5, 6};
  int sortedArray[] = {1, 2, 5, 5, 6, 9};
  int size = sizeof(array) / sizeof(array[0]);

  insertionSort(array, size);

  for (int i = 0; i < size; i++) {
    EXPECT_EQ(array[i], sortedArray[i]);
  }
}

TEST(AlgorithmsTest, BinarySearchTest_Found) {
  int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int size = sizeof(array) / sizeof(array[0]);
  int item = 5;
  int pos = -1;

  binarySearch(array, 0, size - 1, item, pos);

  EXPECT_EQ(pos, 4);
}

TEST(AlgorithmsTest, BinarySearchTest_NotFound) {
  int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int size = sizeof(array) / sizeof(array[0]);
  int item = 10;
  int pos = -1;

  binarySearch(array, 0, size - 1, item, pos);

  EXPECT_EQ(pos, -1);
}
