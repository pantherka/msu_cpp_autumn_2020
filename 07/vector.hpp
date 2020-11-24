#include <iostream>
#include <iterator>

#pragma once

template <class T>
class Allocator
{
    public:
    using value_type = T;
    T* allocate(size_t n)
    {
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }
    void deallocate(T* data, size_t n)
    {
        ::operator delete(static_cast<void *>(data));
    }
};

template <class T, class Alloc = Allocator<T>>  
class Vector
{
    T* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;
    Alloc allocator_;

    class Iterator : public std::iterator<std::random_access_iterator_tag, T>
    {
        T* pos_ = nullptr;
    public:
        Iterator(const Iterator& other) { pos_ = other.pos_; };
        Iterator(T* other) { pos_ = other; };
        Iterator& operator=(const Iterator& other)
        {
            if (this == &other)
            {
                return *this;
            }
            pos_ = other.pos_;
            return *this;
        };
        ~Iterator() = default;
        Iterator& operator+=(size_t n) { pos_ += n; return *this; };
        Iterator operator+(size_t n) const
        {
            Iterator result(*this);
            result += n;
            return result;
        };
        Iterator& operator++() { ++pos_; return *this; };
        Iterator& operator-=(size_t n) { pos_ -= n; return *this; };
        Iterator operator-(size_t n) const
        {
            Iterator result(*this);
            result -= n;
            return result;
        };
        Iterator& operator--() { --pos_; return *this; }
        T& operator*() const { return *pos_; }
        T* operator->() const { return pos_; }
        bool operator<(const Iterator& other) const { return pos_ < other.pos_; }
        bool operator==(const Iterator& other) const { return pos_ == other.pos_; }
        bool operator!=(const Iterator& other) const { return pos_ != other.pos_; }
        bool operator<=(const Iterator& other) const { return pos_ <= other.pos_; }
        bool operator>=(const Iterator& other) const { return pos_ >= other.pos_; }
        bool operator>(const Iterator& other) const { return pos_ > other.pos_; }

    };
    
    class ConstIterator : public std::iterator<std::random_access_iterator_tag, T>
    {
        T* pos_ = nullptr;
    public:
        ConstIterator(const ConstIterator& other) { pos_ = other.pos_; };
        ConstIterator(T* other) { pos_ = other; };
        ConstIterator& operator=(const ConstIterator& other)
        {
            if (this == &other)
            {
                return *this;
            }
            pos_ = other.pos_;
            return *this;
        };
        ~ConstIterator() = default;
        ConstIterator& operator+=(size_t n) { pos_ += n; return *this; };
        ConstIterator operator+(size_t n) const 
        {
            ConstIterator result(*this);
            result += n;
            return result;
        };
        ConstIterator& operator++() { ++pos_; return *this; };
        ConstIterator& operator-=(size_t n) { pos_ -= n; return *this; };
        ConstIterator operator-(size_t n) const 
        {
            ConstIterator result(*this);
            result -= n;
            return result;
        };
        ConstIterator& operator--() { --pos_; return *this; }
        const T& operator*() const { return *pos_; }
        const T* operator->() const { return pos_; }
        bool operator<(const ConstIterator& other) const { return pos_ < other.pos_; }
        bool operator==(const ConstIterator& other) const { return pos_ == other.pos_; }
        bool operator!=(const ConstIterator& other) const { return pos_ != other.pos_; }
        bool operator<=(const ConstIterator& other) const { return pos_ <= other.pos_; }
        bool operator>=(const ConstIterator& other) const { return pos_ >= other.pos_; }
        bool operator>(const ConstIterator& other) const { return pos_ > other.pos_; }

    };

    public:
    using value_type = T;

    Vector();
    Vector(size_t n);
    Vector(const Vector<T, Alloc>& other);
    Vector(Vector<T, Alloc>&& other);
    Vector<T, Alloc>& operator=(const Vector<T, Alloc>& other);
    Vector<T, Alloc>& operator=(Vector<T, Alloc>&& other);
    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }

    Iterator begin() { return Iterator(data_); }
    ConstIterator begin() const { return ConstIterator(data_); }
    Iterator end() { return Iterator(data_ + size_); }
    ConstIterator end() const { return ConstIterator(data_ + size_); }
    std::reverse_iterator<Iterator> rbegin() { return std::reverse_iterator<Iterator>((this->end())); }
    std::reverse_iterator<ConstIterator> rbegin() const { return std::reverse_iterator<ConstIterator>((this->end())); }
    std::reverse_iterator<Iterator> rend() { return std::reverse_iterator<Iterator>((this->begin())); }
    std::reverse_iterator<ConstIterator> rend() const { return std::reverse_iterator<ConstIterator>((this->begin())); }

    void resize(size_t n);
    void reserve(size_t n);
    void push_back(T&& elem);
    template<class ...Args>
    void emplace_back(Args&&... args);
    void pop_back();
    const T& operator[](size_t n) const;
    T& operator[](size_t n);
    void clear();
    ~Vector()
    {
        if (data_)
        {
            allocator_.deallocate(data_, capacity_); // переписать под свой аллокатор
        }
    }

};

/*template <class T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator=(const Iterator& other)
*/

template <class T, class Alloc>
Vector<T, Alloc>::Vector()
{
    data_ = allocator_.allocate(1);
    capacity_ = 1;
    size_ = 0;
}

template <class T, class Alloc>
Vector<T, Alloc>::Vector(size_t n)
{
    data_ = allocator_.allocate(n);
    capacity_ = n;
    size_ = 0;
}

template <class T, class Alloc>
Vector<T, Alloc>::Vector(const Vector<T, Alloc>& other) : capacity_(other.capacity_), size_(other.size_)
{
    std::copy(other.data_, other.data_ + capacity_, data_);
}

template <class T, class Alloc>
Vector<T, Alloc>& Vector<T, Alloc>::operator=(const Vector<T, Alloc>& other) 
{
    if (this == &other)
    {
        return *this;
    }
    if (data_)
    {
        this->clear();
        allocator_.deallocate(data_, capacity_);
    }
    capacity_ = other.capacity_;
    size_ = other.size_;
    std::copy(other.data_, other.data_ + other.capacity_, data_);
    return *this;
}

template <class T, class Alloc>
Vector<T, Alloc>::Vector(Vector<T, Alloc>&& other) : capacity_(other.capacity_), size_(other.size_)
{
    data_ = other.data_;
    other.data_ = nullptr;
    other.capacity_ = 0;
    other.size_ = 0;
}

template <class T, class Alloc>
Vector<T, Alloc>& Vector<T, Alloc>::operator=(Vector<T, Alloc>&& other)
{
    if (this == &other)
    {
        return *this;
    }
    data_ = other.data_;
    capacity_ = std::move(other.capacity_);
    size_ = std::move(other.size_);
    other.data_ = nullptr;
    other.capacity_ = 0;
    other.size_ = 0;
}

template <class T, class Alloc>
void Vector<T, Alloc>::resize(size_t n)
{
    if (n > capacity_)
    {
        this->reserve(n);
    }
    size_ = n;
}

template <class T, class Alloc>
void Vector<T, Alloc>::reserve(size_t n)
{
    if (n > capacity_)
    {
        T* tmp = allocator_.allocate(n);
        if (data_) 
        {
            for (size_t i = 0; i < size_; ++i)
            {
                tmp[i] = data_[i];
            }
            allocator_.deallocate(data_, capacity_);
        }
        data_ = tmp;
        capacity_ = n;
    }
}

template <class T, class Alloc>
void Vector<T, Alloc>::push_back(T&& elem)
{
    if (size_ == capacity_)
    {
        this->reserve(2 * capacity_);
    }
    this->operator[](size_) = elem;
    ++size_;
}

template <class T, class Alloc>
template <class... Args>
void Vector<T, Alloc>::emplace_back(Args&&... args)
{
    if (size_ == capacity_)
    {
        this->reserve(2 * capacity_);
    }
    this->operator[](size_) = T(args...);
    ++size_;
}


template <class T, class Alloc>
void Vector<T, Alloc>::pop_back()
{
    size_--;
    // (data_[size_]).~T();
}

template <class T, class Alloc>
const T& Vector<T, Alloc>::operator[](size_t n) const
{
    return data_ + n;
}

template <class T, class Alloc>
T& Vector<T, Alloc>::operator[](size_t n)
{
    return *(data_ + n);
}

template <class T, class Alloc>
void Vector<T, Alloc>::clear()
{
    size_ = 0;
}
