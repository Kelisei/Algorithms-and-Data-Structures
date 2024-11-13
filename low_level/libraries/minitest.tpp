#pragma once
#ifndef MINITEST_TPP
#define MINITEST_TPP
#include "minitest.hpp"
#include <type_traits>
#include <chrono>
#include <iostream>

template <typename T>
bool assertEquality(T a, T b)
{
    if (a != b)
    {
        throw std::runtime_error("Values are not equal at line " + std::to_string(__LINE__));
    }
    return true;
}

template <typename T>
bool assertDifference(T a, T b)
{
    if (a == b)
    {
        throw std::runtime_error("Values are not different at line " + std::to_string(__LINE__));
    }
    return true;
}

template <typename T>
bool assertTrue(T a)
{
    if (!a)
    {
        throw std::runtime_error("Value is not true at line " + std::to_string(__LINE__));
    }
    return true;
}

template <typename T>
bool assertFalse(T a)
{
    if (a)
    {
        throw std::runtime_error("Value is not false at line " + std::to_string(__LINE__));
    }
    return true;
}

template <typename T, typename std::enable_if<std::is_pointer<T>::value, int>::type>
bool assertNull(T a)
{
    if (a != nullptr)
    {
        throw std::runtime_error("Pointer is not null at line " + std::to_string(__LINE__));
    }
    return true;
}

template <typename T, typename std::enable_if<std::is_pointer<T>::value, int>::type>
bool assertNotNull(T a)
{
    if (a == nullptr)
    {
        throw std::runtime_error("Pointer is null at line " + std::to_string(__LINE__));
    }
    return true;
}
#endif