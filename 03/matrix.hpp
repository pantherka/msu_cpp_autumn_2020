#include <iostream>

#ifndef MATRIX_H
#define MATRIX_H

class Proxy {
    int* array;
    size_t len;
public:
    Proxy(int* &array, size_t len) : array(array), len(len) {};
    int& operator[](size_t col) const;
};

class Matrix {
    size_t rows, columns;
    int **matrix = nullptr;
public:
    Matrix(size_t rows, size_t columns);
    size_t Rows() const { return this->rows; };
    size_t Columns() const { return this->columns; };
    bool operator==(const Matrix &other) const;
    bool operator!=(const Matrix &other) const;
    Matrix& operator*=(int n);
    Matrix operator+(const Matrix& other) const;
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);
    Proxy operator[](size_t row) const;
    friend std::ostream& operator<<(std::ostream& ostream, const Matrix& matrix);
    ~Matrix();
};

#endif
