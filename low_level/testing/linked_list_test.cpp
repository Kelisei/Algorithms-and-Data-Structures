#include "minitest.hpp"
#include "linked_list.hpp"


void registerLinkedListTests() {
    ADD_TEST(testLinkedListAdd, []() {
        LinkedList<int> list;
        list.add(1);
        list.add(2);
        list.add(3);
        assertEquality(list.size(), 3);
        assertEquality(list.get(0), 1);
        assertEquality(list.get(1), 2);
        assertEquality(list.get(2), 3);
    });

    ADD_TEST(testLinkedListRemove, []() {
        LinkedList<int> list;
        list.add(1);
        list.add(2);
        list.add(3);
        list.remove(2);
        assertEquality(list.size(), 2);
        assertEquality(list.get(0), 1);
        assertEquality(list.get(1), 3);
    });

    ADD_TEST(testLinkedListInsert, []() {
        LinkedList<int> list;
        list.add(1);
        list.add(3);
        list.add(4);
        list.insert(1, 1); // Add insert in the second element, move the rest to the right
        assertEquality(list.size(), 4);
        assertEquality(list.get(0), 1);
        assertEquality(list.get(1), 1);
        assertEquality(list.get(2), 3);
        assertEquality(list.get(3), 4);
    });

    ADD_TEST(testLinkedListContains, []() {
        LinkedList<int> list;
        list.add(1);
        list.add(2);
        list.add(3);
        assertTrue(list.contains(2));
        assertFalse(list.contains(4));
    });

    ADD_TEST(testLinkedListIsEmpty, []() {
        LinkedList<int> list;
        assertTrue(list.isEmpty());
        list.add(1);
        assertFalse(list.isEmpty());
    });

    ADD_TEST(testLinkedListSize, []() {
        LinkedList<int> list;
        list.add(1);
        list.add(2);
        list.add(3);
        assertEquality(list.size(), 3);
    });

    ADD_TEST(testLinkedListClear, []() {
        LinkedList<int> list;
        list.add(1);
        list.add(2);
        list.add(3);
        list.clear();
        assertTrue(list.isEmpty());
        assertEquality(list.size(), 0);
    });

    ADD_TEST(testLinkedListGet, []() {
        LinkedList<int> list;
        list.add(1);
        list.add(2);
        list.add(3);
        assertEquality(list.get(0), 1);
        assertEquality(list.get(1), 2);
        assertEquality(list.get(2), 3);
    });

    ADD_TEST(testLinkedListSet, []() {
        LinkedList<int> list;
        list.add(1);
        list.add(2);
        list.add(3);
        list.set(4, 1);
        assertEquality(list.get(1), 4);
    });

    ADD_TEST(testLinkedListToArray, []() {
        LinkedList<int> list;
        list.add(1);
        list.add(2);
        list.add(3);
        int *arr = list.toArray();
        assertEquality(arr[0], 1);
        assertEquality(arr[1], 2);
        assertEquality(arr[2], 3);
        delete[] arr;
    });

    ADD_TEST(testLinkedListSubList, []() {
        LinkedList<int> list;
        list.add(1);
        list.add(2);
        list.add(3);
        List<int> *sublist = list.subList(1, 2);
        assertEquality(sublist->size(), 2);
        assertEquality(sublist->get(0), 2);
        assertEquality(sublist->get(1), 3);
        delete sublist;
    });

    ADD_TEST(testLinkedListIndexOf, []() {
        LinkedList<int> list;
        list.add(1);
        list.add(2);
        list.add(3);
        assertEquality(list.indexOf(2), 1);
        assertEquality(list.indexOf(4), -1);
    });

    ADD_TEST(testLinkedListLastIndexOf, []() {
        LinkedList<int> list;
        list.add(1);
        list.add(2);
        list.add(3);
        list.add(2);
        assertEquality(list.lastIndexOf(2), 3);
        assertEquality(list.lastIndexOf(4), -1);
    });

    ADD_TEST(testLinkedListEquality, []() {
        LinkedList<int> list1;
        list1.add(1);
        list1.add(2);
        list1.add(3);

        LinkedList<int> list2;
        list2.add(1);
        list2.add(2);
        list2.add(3);

        assertTrue(list1 == list2);

        list2.add(4);
        assertFalse(list1 == list2);
    });

    ADD_TEST(testLinkedListHashCode, []() {
        LinkedList<int> list;
        list.add(1);
        list.add(2);
        list.add(3);
        std::size_t hash = list.hashCode();
        assertDifference(hash, std::size_t(0));
    });

    ADD_TEST(testLinkedListToString, []() {
        LinkedList<int> list;
        list.add(1);
        list.add(2);
        list.add(3);
        assertEquality(list.toString(), std::string("[1, 2, 3]"));
    });

    ADD_TEST(testLinkedListIterator, []() {
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
    });
}
