#include <cstddef>
#ifndef ALLOCATOR_H
#define ALLOCATOR_H

/*
alloc(0) возвращает nullptr всегда
makeAllocator(0) не делает ровным счётом ничего
повторный вызов makeAllocator() удаляет старую память и выделяет новую, offset сбрасывается в ноль
*/

class Allocator
{
    char *point = nullptr;
    size_t offset = 0;
    size_t end = 0;
public:
    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
    ~Allocator();
};

#endif