#include <cstddef>
#ifndef ALLOCATOR_H
#define ALLOCATOR_H

class Allocator
{
    char *point;
    size_t offset = 0;
    size_t end = 0;
public:
    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
    ~Allocator();
};

#endif