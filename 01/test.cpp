#include "allocator.h"
#include <iostream>
#include <cassert>

int main() {
    const int size = 100;
    Allocator *al =  new Allocator;
    al->makeAllocator(size);
    char *ans;
    assert(al->alloc(2 * size) == nullptr); // проверка на выделение больше, чем вообще есть
    ans = al->alloc(size / 2);
    assert(ans != nullptr); // проверка на выделение доступного количества
    assert((al->alloc(size / 4) - ans) == (size / 2)); // проверка, что счётчик сдвинулся на величину прошлого вызова
    assert(al->alloc(size / 2) == nullptr);
    al->reset();
    assert(al->alloc(size - 1) != nullptr); // корректность работы reset
    delete al;
    
    const int size_new = 10000;
    const int iter_cycle = 10;
    Allocator *al_new = new Allocator;
    assert(al_new->alloc(1) == nullptr); 
    // неясно, может ли пользователь вызвать alloc до makeAllocator, но оно работает
    al_new->makeAllocator(size);
    al_new->makeAllocator(size_new); // второй вызов makeAllocator, старое чистится, новое выделяется
    for (size_t i = 0; i < iter_cycle; ++i) {
        assert(al_new->alloc(size_new / iter_cycle) != nullptr);
    }
    // проверка корректности последовательных запросов, к этому моменту выбраны ровно 10000 байт
    assert((al_new->alloc(1) == nullptr));
    assert(al_new->alloc(0) == nullptr);
    al_new->makeAllocator(0);
    assert(al_new->alloc(0) == nullptr);
    al_new->makeAllocator(size);
    assert(al_new->alloc(size / 2) != nullptr);
    assert(al_new->alloc(size) == nullptr);
    delete al_new;
    
    Allocator *al_second = new Allocator; // проверка на выход без makeAllocator
    assert(al_second->alloc(0) == nullptr); 
    delete al_second;
    std::cout << "All tests passed " << std::endl;
    return 0;
}