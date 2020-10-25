#include "matrix.hpp"

int& Proxy::operator[](size_t col) const {
    if (col >= this->len) {
        throw std::out_of_range("");
    }
    return array[col];
}

Matrix::Matrix(size_t rows, size_t columns) {
    this->rows = rows;
    this->columns = columns;
    this->matrix = new int*[rows];
    for (size_t i = 0; i < rows; ++i) {
        matrix[i] = new int[columns];
        for (size_t j = 0; j < columns; ++j) {
            matrix[i][j] = 0;
        }
    }
}

Proxy Matrix::operator[](size_t row) const {
    if (row >= this->rows) {
        throw std::out_of_range("");
    }
    return Proxy(matrix[row], columns);
}

bool Matrix::operator==(const Matrix& other) const {
    bool answer = false;
    if ((this->rows != other.rows) || (this->columns != other.columns)) {
        return answer;
    }
    for (size_t i = 0; i < this->rows; ++i) {
        for (size_t j = 0; j < this->columns; ++j) {
            if (this->operator[](i)[j] != other[i][j]) {
                return answer;
            }
        }
    }
    answer = true;
    return answer;
}

bool Matrix::operator!=(const Matrix& other) const {
    bool answer = true;
    if ((this->rows != other.rows) || (this->columns != other.columns)) {
        return answer;
    }
    for (size_t i = 0; i < this->rows; ++i) {
        for (size_t j = 0; j < this->columns; ++j) {
            if (this->operator[](i)[j] != other[i][j]) {
                return answer;
            }
        }
    }
    answer = false;
    return answer;
}

Matrix& Matrix::operator*=(int n) {
    for (size_t i = 0; i < this->rows; ++i) {
        for (size_t j = 0; j < this->columns; ++j) {
            this->operator[](i)[j] *= n;
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream& ostream, const Matrix& matrix) {
    for (size_t i = 0; i < matrix.rows; ++i) {
        for (size_t j = 0; j < matrix.columns; ++j) {
            ostream << matrix[i][j] << ' ';
        }
        ostream << std::endl;
    }
    return ostream;
}

Matrix::~Matrix() {
    for (size_t i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

Matrix Matrix::operator+(const Matrix& other) const {
    if ((this->rows != other.rows) || (this->columns != other.columns)) {
        throw std::out_of_range("");
    }
    Matrix answer(other.rows, other.columns);
    for (size_t i = 0; i < other.rows; ++i) {
        for (size_t j = 0; j < other.columns; ++j) {
            answer[i][j] = this->operator[](i)[j] + other[i][j];
        }
    } 
    return answer;
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) {
        return *this;
    }
    rows = other.rows;
    columns = other.columns;

    if (matrix) {
        for (size_t i = 0; i < rows; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    matrix = new int*[rows];
    for (size_t i = 0; i < rows; ++i) {
        matrix[i] = new int[columns];
        for (size_t j = 0; j < columns; ++j) {
            matrix[i][j] = other.matrix[i][j];
        }
    }
    return *this;
}

Matrix::Matrix(const Matrix& other) : rows(other.rows), columns(other.columns) {
     if (matrix) {
        for (size_t i = 0; i < rows; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    matrix = new int*[rows];
    for (size_t i = 0; i < rows; ++i) {
        matrix[i] = new int[columns];
        for (size_t j = 0; j < columns; ++j) {
            matrix[i][j] = other.matrix[i][j];
        }
    }
}
