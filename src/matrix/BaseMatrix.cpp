#include "BaseMatrix.h"

template < typename T >
BaseMatrix<T>::BaseMatrix(const BaseMatrix<T> &other) {
    for (size_t i = 0; i < height(); ++i) {
        for (size_t j = 0; j < width(); ++j) {
            this[i][j] = *(other[i][j]);
        }
    }
}