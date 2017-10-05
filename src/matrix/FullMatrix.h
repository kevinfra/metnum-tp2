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
    FullMatrix(size_t h, size_t w) {
        init(h, w, 0);
    }

    FullMatrix(size_t h, size_t w, const T& def) {
        init(h, w, def);
    }

    FullMatrix(T **arr, u_int height, u_int width) {
        init(height, width, 0);
        for (u_int i = 0; i < height; ++i) {
            for (u_int j = 0; j < width; ++j) {
                (*this)[i][j] = arr[i][j];
            }
        }
    }

    FullMatrix(std::initializer_list<std::vector<T>> list) : _grid(list) {
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

    virtual MatrixRef<T> makeNew(size_t height, size_t width) const {
        return std::make_shared<FullMatrix<T>>(height, width);
    }

    // special generators

    static FullMatrix zero(size_t size) {
        return FullMatrix(size, size, 0);
    }

    static FullMatrix identity(size_t size) {
        FullMatrix mx(size, size, 0);
        for (size_t i = 0; i < size; ++i) {
            mx[i][i] = 1;
        }
        return mx;
    }

protected:
    FullMatrix() {}

    grid<T> _grid;

private:
    void init(size_t h, size_t w, T def) {
        row<T> r(w, def);
        for (size_t i = 0; i < h; ++i) {
            _grid.push_back(r);
        }
    }

};


#endif //METNUM_TP2_FULLMATRIX_H
