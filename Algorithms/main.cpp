#include <iostream>
static void insertionSort(int array[], int size) {
	int pos, item;
	for (int i = 0; i < size; i++) {
		pos = i;
		for (int j = i + 1; j < size; j++) {
			if (array[j] < array[pos]) { pos = j; }
		}
		item = array[pos];
		array[pos] = array[i];
		array[i] = item;
	}
}
static void binarySearch(int array[], int first, int last, int item, int &pos){
	int mid;
	if (first > last) { pos = -1; }
	else {
		mid = (first + last) / 2;
		if (item == array[mid]) { pos = mid; }
		else {
			if (item < array[mid]) { binarySearch(array, first, (mid - 1), item, pos); }
			else { binarySearch(array, (mid + 1), last, item, pos); }
		}
	}
}
int main() {
	int numbers[] = { 1, 1, 2, 9, 8, 6, 10, 999, 100, 222, 0 };
	int size = sizeof(numbers) / sizeof(numbers[0]);
	for (int number : numbers) {
		std::cout << number << std::endl;
	}
	std::cout << std::endl;
	insertionSort(numbers, size);


	for (int number : numbers) {
		std::cout << number << std::endl;
	} 
	std::cout << std::endl;
	int pos = 0;
	binarySearch(numbers, 0, size, 8, pos);
	std::cout << pos << std::endl;
}