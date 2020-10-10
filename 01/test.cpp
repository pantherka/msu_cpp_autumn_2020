#include "allocator.h"
#include <iostream>
#include <cassert>

int main() {
    const int size = 100;
    Allocator *al =  new Allocator;
    al->makeAllocator(size);
    char *ans;
    assert((al->alloc(2 * size) == nullptr)); // проверка на выделение больше, чем вообще есть
    ans = al->alloc(size / 2);
    assert((ans != nullptr)); // проверка на выделение доступного количества
    assert(((al->alloc(size / 4) - ans) == (size / 2))); // проверка, что счётчик сдвинулся на величину прошлого вызова
    assert((al->alloc(size / 2) == nullptr));
    al->reset();
    assert((al->alloc(size - 1) != nullptr)); // корректность работы reset
    delete al;
    
    const int size_new = 10000;
    const int iter_cycle = 10;
    Allocator *al_new = new Allocator;
    assert((al_new->alloc(1) == nullptr)); 
    // неясно, может ли пользователь вызвать alloc до makeAllocator, но оно работает
    al_new->makeAllocator(size_new);
    for (size_t i = 0; i < iter_cycle; ++i) {
        assert((al_new->alloc(size_new / iter_cycle) != nullptr));
    }
    // проверка корректности последовательных запросов, к этому моменту выбраны ровно 10000 байт
    assert((al->alloc(1) == nullptr)); 
    std::cout << "All tests passed " << std::endl;
    delete al_new;
    return 0;
}