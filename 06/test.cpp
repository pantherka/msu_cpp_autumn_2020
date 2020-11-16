#include "format.hpp"
#include <cassert>
#include <iostream>

int main()
{
    const std::string p = "{1}+{1} = {0}";
    std::cout << format(p, 2, "one") << std::endl;
    std::cout << format(p, 1, "two") << std::endl;
    size_t error_count = 0;
    auto text = format("{1}+{1} = {0}", 2, "one");
    assert(text == "one+one = 2");
    std::cout << text << std::endl;

    try
    {
        text = format("abc} {0}", 1, 2);
    }
    catch(const StringError& e)
    {
        error_count++;
    }
    assert(error_count == 1);

    try
    {
        text = format("abc {0}}", 1, 2);
    }
    catch(const StringError& e)
    {
        error_count++;
    }
    assert(error_count == 2);

    try
    {
        text = format("abc {{0}", 1, 2);
    }
    catch(const StringError& e)
    {
        error_count++;
    }
    assert(error_count == 3);

    try
    {
        text = format("abc {3}", 1, 2, 3);
    }
    catch(const ArgumentError& e)
    {
        error_count++;
    }
    assert(error_count == 4);
    
    std::cout << "All test passed." << std::endl;
    return 0;
}