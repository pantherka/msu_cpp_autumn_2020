#include "bigint.hpp"
#include <iostream>
#include <cassert>

int main() {
    BigInt a = 1; // проверка конструктора из числа
    BigInt b("123456789012345678901234567890"); // проверка конструктора из строки
    BigInt c = a * b + 2;   
    BigInt d;
    d = std::move(c);
    assert(c == BigInt()); // проверка корректности обнуления
    assert(b - b == 0);
    assert(b + (-b) == 0);
    a = d + b;
    assert(a == b * 2 + 2);
    assert(BigInt(0) == 0);
    assert(BigInt("0") == BigInt(0));
    assert(BigInt(-55) == BigInt("-55")); // корректность определения через число и строку

    BigInt e = a;
    assert(e <= a);
    assert(e >= a);
    assert(e == a);
    assert(!(e < a));
    assert(!(e > a));
    assert(BigInt(-5) < -4);
    assert(BigInt(1) > -1);
    std::cout << a << std::endl;
    std::cout << "All test passed." << std::endl;
    return 0;
}