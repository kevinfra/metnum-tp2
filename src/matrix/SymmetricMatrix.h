#ifndef METNUM_TP2_SYMMETRICMATRIX_H
#define METNUM_TP2_SYMMETRICMATRIX_H

#include "BaseMatrix.h"
#include "SparseMatrix.h"
#include "FullMatrix.h"

template < typename T >
class SymmetricMatrix : public virtual BaseMatrix<T> {

    virtual T get(size_t row, size_t col) const {
        if(row < col) {
            return internal_get(col, row);
        } else {
            return internal_get(row, col);
        }
    }

    virtual void set(size_t row, size_t col, const T& val) {
        if(row < col) {
            return internal_set(col, row, val);
        } else {
            return internal_set(row, col, val);
        }
    }

protected:

    virtual T internal_get(size_t row, size_t col) const = 0;

    virtual void internal_set(size_t row, size_t col, const T& val) = 0;
};

template < typename T >
class SymmetricFullMatrix : public SymmetricMatrix<T>, public FullMatrix<T> {
public:
    SymmetricFullMatrix(size_t h, size_t w, const T &def) {
        for (size_t i = 0; i < h; ++i) {
            row<T> r(i, def);
            _grid.push_back(r);
        }
    }
protected:

    virtual T internal_get(size_t row, size_t col) const {
        return FullMatrix::get(row, col);
    }

    virtual void internal_set(size_t row, size_t col, const T& val) {
        FullMatrix::set(row, col, val);
    }

};

template < typename T >
class SymmetricSparseMatrix : public SymmetricMatrix<T>, public SparseMatrix<T> {
public:
    SymmetricSparseMatrix(size_t height, size_t width, const T &def)
            : SparseMatrix(height, width, def) {}
protected:

    virtual T internal_get(size_t row, size_t col) const {
        return SparseMatrix::get(row, col);
    }

    virtual void internal_set(size_t row, size_t col, const T& val) {
        SparseMatrix::set(row, col, val);
    }

};


#endif //METNUM_TP2_SYMMETRICMATRIX_H
