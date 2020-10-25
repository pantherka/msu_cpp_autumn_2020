#include "matrix.hpp"
#include <iostream>
#include <cassert>

int main() {
    
    const size_t rows = 5;
    const size_t cols = 3;

    Matrix m(rows, cols);

    assert(m.Rows() == 5);
    assert(m.Columns() == 3);

    m[1][2] = 5; // строка 1, колонка 2
    assert(m[1][2] == 5);
    std::cout << m << std::endl; // тест на то, что вывод вообще работает

    int elem = -1;
    int exceptions = 0;
    try {
        elem = m[rows][0]; // проверка на выход за границы по первой оси
    }
    catch (const std::out_of_range& e) {
        exceptions++;
    }
    assert(exceptions == 1);

    try {
        elem = m[0][cols]; // проверка на выход за границы по второй оси
    }
    catch (const std::out_of_range& e) {
        exceptions++;
    }
    assert(exceptions == 2);

    m[0][0] = elem;
    double x = m[4][1];

    m *= 3; // умножение на число
    assert(m[1][2] == 15);

    Matrix mat(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            mat[i][j] = i + j;
        }
    }
    Matrix m2 = m + mat; // проверка сложения
    assert(m2[1][2] == 18); // mat[1][2] = 3
    assert(m[0][0] == -3);
    assert((m == mat) == false); // проверка (не)равенства матриц
    assert(m != mat);
    
    Matrix m3 = mat + m;
    assert(m3 == m2); 

    std::cout << "All tests passed." << std::endl;
    return 0;
}