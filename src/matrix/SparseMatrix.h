#ifndef METNUM_TP2_SPARSEMATRIX_H
#define METNUM_TP2_SPARSEMATRIX_H

#include <cstddef>
#include <map>
#include "Matrix.h"

typedef std::pair<size_t, size_t> coord;

template < typename T >
class SparseMatrix : public virtual Matrix<T> {
public:
    SparseMatrix(size_t height, size_t width) : h(height), w(width), emptyVal(0) {}

    SparseMatrix(size_t height, size_t width, const T& def) : h(height), w(width), emptyVal(def) {}

    virtual T get(size_t row, size_t col) const {
        auto it = grid.find(coord(row, col));
        if(it == grid.end()) {
            return emptyVal;
        }
        return it->second;
    }

    virtual void set(size_t row, size_t col, const T& val) {
        coord key(row, col);
        if(val == emptyVal) {
            grid.erase(key);
        } else {
            grid[key] = val;
        }
    }

    virtual size_t height() const {
        return h;
    }

    virtual size_t width() const {
        return w;
    }

    virtual MatrixRef<T> makeNew(size_t height, size_t width) const {
        return std::make_shared<SparseMatrix>(height, width, emptyVal);
    }

    // special generators

    static SparseMatrix zero(size_t size) {
        return SparseMatrix(size, size, 0);
    }

    static SparseMatrix identity(size_t size) {
        SparseMatrix mx(size, size, 0);
        for (size_t i = 0; i < size; ++i) {
            mx[i][i] = 1;
        }
        return mx;
    }

protected:
    std::map< coord, T > grid;

    size_t h;
    size_t w;
    T emptyVal;
};



#endif //METNUM_TP2_SPARSEMATRIX_H
