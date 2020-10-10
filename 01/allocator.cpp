#include "allocator.h"

void Allocator::makeAllocator(size_t maxSize) {
    point = new char[maxSize];
    offset = 0;
    end = maxSize;
}
char* Allocator::alloc(size_t size) {
    char* answer = nullptr;
    if (offset + size > end) {
        return answer;
    }
    answer = point + offset;
    offset += size;
    return answer;
}
void Allocator::reset() {
    offset = 0;
}
Allocator::~Allocator() {
    delete[] point;
}
