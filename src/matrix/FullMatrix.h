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
        init(h, w, static_cast<T>(0));
    }

    FullMatrix(size_t h, size_t w, const T& def) {
        init(h, w, def);
    }

    FullMatrix(T **arr, unsigned int height, unsigned int width) {
        init(height, width, static_cast<T>(0));
        for (unsigned int i = 0; i < height; ++i) {
            for (unsigned int j = 0; j < width; ++j) {
                (*this)[i][j] = arr[i][j];
            }
        }
    }

    FullMatrix(const vector<vector<T>>& list) : _grid(list) {
    }

    FullMatrix(const std::initializer_list<vector<T>> list) : _grid(list) {
    }

    virtual T internal_get(size_t row, size_t col) const {
        return _grid[row][col];
    }

    virtual void internal_set(size_t row, size_t col, const T& val) {
        _grid[row][col] = val;
    }

    virtual size_t internal_height() const {
        return _grid.size();
    }

    virtual size_t internal_width() const {
        if(_grid.empty()) {
            return 0;
        }
        return _grid[0].size();
    }

    virtual MatrixRef<T> makeNew(size_t height, size_t width) const {
        return create(height, width);
    }

    // special generators

    template< typename... _Args >
    static inline MatrixRef<T> create(_Args&&... __args) {
        return std::make_shared<FullMatrix<T>>(__args ...);
    }

    static FullMatrix zero(size_t size) {
        return FullMatrix(size, size, static_cast<T>(0));
    }

    static FullMatrix identity(size_t size) {
        FullMatrix mx(size, size, static_cast<T>(0));
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
