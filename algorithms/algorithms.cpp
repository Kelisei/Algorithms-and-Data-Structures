#include <iostream>
// Given an array and a size this algorithm will swap them in O(N^2)
// By, ensentially, going one by one element and checking if another
// one in the array is lower.
void insertionSort(int array[], int size) {
  int pos, item;
  for (int i = 0; i < size; i++) {
    pos = i;
    for (int j = i + 1; j < size; j++) {
      if (array[j] < array[pos]) {
        pos = j;
      }
    }
    item = array[pos];
    array[pos] = array[i];
    array[i] = item;
  }
}
// This a implementation of binary search using recursion (high overhead).
// You have to give the array, 0 as first index, and size of array as last
// index. item is the element to find and pos is what is going to be the
// position if found.
void binarySearch(int array[], int first, int last, int item, int &pos) {
  int mid;
  if (first > last) {
    pos = -1;
  } else {
    mid = (first + last) / 2;
    if (item == array[mid]) {
      pos = mid;
    } else {
      if (item < array[mid]) {
        binarySearch(array, first, (mid - 1), item, pos);
      } else {
        binarySearch(array, (mid + 1), last, item, pos);
      }
    }
  }
}
