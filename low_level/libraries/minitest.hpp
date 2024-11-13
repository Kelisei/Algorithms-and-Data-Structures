#pragma once
#ifndef MINITEST_HPP
#define MINITEST_HPP

#include <type_traits>
#include <vector>
#include <functional>
#include <string>
template <typename T>
bool assertEquality(T a, T b);

template <typename T>
bool assertDifference(T a, T b);

template <typename T>
bool assertTrue(T a);

template <typename T>
bool assertFalse(T a);

template <typename T, typename std::enable_if<std::is_pointer<T>::value, int>::type>
bool assertNull(T a);

template <typename T, typename std::enable_if<std::is_pointer<T>::value, int>::type>
bool assertNotNull(T a);

class Test
{
private:
    std::vector<std::tuple<std::string, std::function<void()>>> tests;

public:
    Test();
    void addTest(const std::string &testName, std::function<void()> test);
    void run();
};

extern Test testSuite;
// Macro to add a test to the suite (with static initialization)
#define ADD_TEST(testName, testFunction) \
    static bool testName##_registered = []() { \
        testSuite.addTest(#testName, testFunction); \
        return true; \
    }(); 

// Macro to run all registered tests
#define RUN_TESTS() \
    testSuite.run()


#include "minitest.tpp"

#endif