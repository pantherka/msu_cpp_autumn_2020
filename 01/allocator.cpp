#include "allocator.h"

void Allocator::makeAllocator(size_t maxSize) {
    if (maxSize == 0) {
        return;
    }
    if (point != nullptr) {
        delete[] point;
    }
    point = new char[maxSize];
    offset = 0;
    end = maxSize;
}
char* Allocator::alloc(size_t size) {
    char* answer = nullptr;
    if ((point == nullptr) || (size == 0) || (offset + size > end)) {
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
    if (point != nullptr) {
        delete[] point;
    }
}
