#include "Matrix.h"

template < typename T >
Matrix<T>::Matrix(const Matrix<T> &other) {
    for (size_t i = 0; i < height(); ++i) {
        for (size_t j = 0; j < width(); ++j) {
            this[i][j] = *(other[i][j]);
        }
    }
}