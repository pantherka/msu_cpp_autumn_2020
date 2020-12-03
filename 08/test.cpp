#include "threadpool.hpp"
#include <cassert>
#include <chrono>
#include <thread>
#include <iostream>



struct A {};

void foo(const A&) {}

int main()
{
    ThreadPool pool(8);

    auto task1 = pool.exec(foo, A());
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    task1.get();

    auto task2 = pool.exec([]() { return 1; });
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    auto answer = task2.get();
    assert(answer == 1);

    std::cout << "All tests passed." << std::endl;
    return 0;
}