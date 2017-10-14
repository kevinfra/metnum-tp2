#ifndef METNUM_TP2_SYMMETRICMATRIX_H
#define METNUM_TP2_SYMMETRICMATRIX_H

#include "Matrix.h"
#include "SparseMatrix.h"
#include "FullMatrix.h"

template < typename T >
class SymmetricMatrix : public virtual Matrix<T> {

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

    bool isSquared() const { return true; };

    bool isSymmetric() const { return true; };

    // if A is symmetric, then At = A
    virtual MatrixRef<T> transpose() const {
        MatrixRef<T> t = makeNew(internal_width(), internal_height());
        t->copyFrom(*this);
        return t;
    }

    // if A is symmetric and A = L -> A = U -> A = D
    virtual bool isDiagonal() const {
        return isLowerTriangular();
    }
};

template < typename T >
class SymmetricFullMatrix : public SymmetricMatrix<T>, public FullMatrix<T> {
public:
    SymmetricFullMatrix(size_t size, const T &def) {
        for (size_t i = 0; i < size; ++i) {
            row<T> r(i, def);
            _grid.push_back(r);
        }
    }
protected:

    virtual T internal_get(size_t row, size_t col) const {
        return FullMatrix::internal_get(row, col);
    }

    virtual void internal_set(size_t row, size_t col, const T& val) {
        FullMatrix::internal_set(row, col, val);
    }

    virtual MatrixRef<T> makeNew(size_t height, size_t width) const {
        return std::make_shared<SymmetricFullMatrix>(height, width);
    }

};

template < typename T >
class SymmetricSparseMatrix : public SymmetricMatrix<T>, public SparseMatrix<T> {
public:
    SymmetricSparseMatrix(size_t size, const T &def)
            : SparseMatrix(size, size, def) {}
protected:

    virtual T internal_get(size_t row, size_t col) const {
        return SparseMatrix::internal_get(row, col);
    }

    virtual void internal_set(size_t row, size_t col, const T& val) {
        SparseMatrix::internal_set(row, col, val);
    }

    virtual MatrixRef<T> makeNew(size_t height, size_t width) const {
        return std::make_shared<SymmetricSparseMatrix>(height, width, emptyVal);
    }

};


#endif //METNUM_TP2_SYMMETRICMATRIX_H
