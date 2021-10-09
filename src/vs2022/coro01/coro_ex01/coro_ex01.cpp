// coro_ex01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <coroutine>

// lazy generator

generator<int> generatorForNumbers(int begin, int inc = 1) {
    for (int i = begin;; i += inc) {
        co_yield i;
    }
}

int main()
{
    std::cout << "Hello World!\n";
}
