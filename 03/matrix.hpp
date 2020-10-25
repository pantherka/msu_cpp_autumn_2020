#include <iostream>

class Proxy {
    int* array;
    size_t len;
public:
    Proxy(int* &array, size_t len) : array(array), len(len) {};
    int& operator[](size_t col) const;
};

class Matrix {
    size_t rows, columns;
    int **matrix;
public:
    Matrix(size_t rows, size_t columns);
    size_t Rows() const { return this->rows; };
    size_t Columns() const { return this->columns; };
    bool operator==(const Matrix &other) const;
    bool operator!=(const Matrix &other) const;
    Matrix& operator*=(int n);
    Proxy operator[](size_t row) const;
    friend std::ostream& operator<<(std::ostream& ostream, const Matrix& matrix);
    ~Matrix();
};

Matrix operator+(const Matrix& first, const Matrix& second);
