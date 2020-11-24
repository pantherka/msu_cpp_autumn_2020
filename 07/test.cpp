#include "vector.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>

struct Data
{
    int x = 0;
    int y = 0;
    Data() = default;
    Data(int x, int y) : x(2 * x), y(y) {}
    ~Data() {}
};

int main()
{
    Vector<int> v;
    assert(v.empty());
    v.resize(5);
    assert(v.size() == 5);
    v.reserve(4);
    assert(v.capacity() == 5);
    
    for (size_t i = 0; i < v.size(); ++i)
    {
        v[i] = i;
        std::cout << v[i] << ' ';
    }
    std::cout << std::endl;
    v.pop_back();
    assert(v.size() == 4);
    v.push_back(4);
    assert(v.size() == 5);
    v.push_back(10);
    assert(v.size() == 6);
    std::cout << v.capacity() << std::endl;
    auto iter = v.begin();
    assert(*iter == 0);
    iter += 2;
    assert(*iter == 2);
    assert(iter > v.begin());
    assert(iter - 2 == v.begin());
    //std::for_each(v.begin(), v.end(), [](int x) { std::cout << x << ' '; });
    // std::cout << std::endl;
    for(auto iter = v.begin(); iter < v.end(); ++iter)
    {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
    std::for_each(v.rbegin(), v.rend(), [](int x) { std::cout << x << ' '; });
    //std::for_each(v.rbegin(), v.rend(), [](int x) { std::cout << x << ' '; });
    std::cout << std::endl;

    v.clear();
    assert(v.size() == 0);

    Vector<Data> data;
    data.reserve(4);
    assert(data.size() == 0);
    assert(data.capacity() == 4);
    data.emplace_back(2, 5);
    data.emplace_back(2, 3);
    assert(data[0].x == 2 * 2);
    data.pop_back();
    assert(data.size() == 1);

    std::cout << "All tests passed." << std::endl;
    return 0;
}