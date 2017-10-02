#ifndef METNUM_TP2_FULLMATRIX_H
#define METNUM_TP2_FULLMATRIX_H

#include <vector>
#include "Matrix.h"

template<typename T>
using row = std::vector<T>;

template<typename T>
using grid = std::vector< row<T> >;

template < typename T >
class FullMatrix : public virtual Matrix<T> {
public:
    FullMatrix(size_t h, size_t w, const T& def) {
        row<T> r(w, def);
        for (size_t i = 0; i < h; ++i) {
            _grid.push_back(r);
        }
    }

    virtual T get(size_t row, size_t col) const {
        return _grid[row][col];
    }

    virtual void set(size_t row, size_t col, const T& val) {
        _grid[row][col] = val;
    }

    virtual size_t height() const {
        return _grid.size();
    }

    virtual size_t width() const {
        if(_grid.empty()) {
            return 0;
        }
        return _grid[0].size();
    }

protected:
    FullMatrix() {}


    grid<T> _grid;
};


#endif //METNUM_TP2_FULLMATRIX_H
