#ifndef METNUM_TP2_SPARSEMATRIX_H
#define METNUM_TP2_SPARSEMATRIX_H

#include <cstddef>
#include <map>
#include "Matrix.h"

typedef std::pair<size_t, size_t> coord;

template < typename T >
class SparseMatrix : public virtual Matrix<T> {
public:
    SparseMatrix(size_t height, size_t width, const T& def) : h(height), w(width), emptyVal(def) {}

    virtual T get(size_t row, size_t col) const {
        auto it = grid.find(coord(row, col));
        if(it == grid.end()) {
            return emptyVal;
        }
        return it->second;
    }

    virtual void set(size_t row, size_t col, const T& val) {
        grid.insert(std::pair<coord, T>(coord(row, col), val));
    }

    virtual size_t height() const {
        return h;
    }

    virtual size_t width() const {
        return w;
    }


private:
    std::map< coord, T > grid;

    size_t h;
    size_t w;
    T emptyVal;
};



#endif //METNUM_TP2_SPARSEMATRIX_H
