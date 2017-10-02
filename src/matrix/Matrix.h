#ifndef METNUM_TP2_BASEMATRIX_H
#define METNUM_TP2_BASEMATRIX_H

#include <cstddef>

template < typename T >
class Matrix {
public:
    class Unit {
    public:
        Unit(size_t r, size_t c, Matrix& mx) : row(r), col(c), matrix(mx) {}

        operator T() const {
            return matrix.get(row, col);
        }

        void operator=(const T& other) {
            matrix.set(row, col, other);
        }

    private:
        size_t row;
        size_t col;
        Matrix& matrix;
    };

    class ConstUnit {
    public:
        ConstUnit(size_t r, size_t c, const Matrix& mx) : row(r), col(c), matrix(mx) {}

        operator T() const {
            return matrix.get(row, col);
        }

    private:
        size_t row;
        size_t col;
        const Matrix& matrix;
    };

    class Row {
    public:
        Row(size_t pos, Matrix& mx) : row(pos), matrix(mx) {}

        Unit operator[](size_t pos) const {
            return Unit(row, pos, matrix);
        }

        size_t size() const {
            return matrix.width();
        }

    private:

        size_t row;
        Matrix& matrix;
    };

    class ConstRow {
    public:
        ConstRow(size_t pos, const Matrix& mx) : row(pos), matrix(mx) {}

        ConstUnit operator[](size_t pos) const {
            return ConstUnit(row, pos, matrix);
        }

        size_t size() const {
            return matrix.width();
        }

    private:

        size_t row;
        const Matrix& matrix;
    };

    Matrix() {}

    Matrix(const Matrix& other);

    virtual ~Matrix() {}

    virtual Row operator[](size_t pos) {
        return Row(pos, *this);
    }

    virtual ConstRow operator[](size_t pos) const {
        return ConstRow(pos, *this);
    }

    virtual T get(size_t row, size_t col) const = 0;

    virtual void set(size_t row, size_t col, const T& val) = 0;

    virtual size_t width() const = 0;

    virtual size_t height() const = 0;

    bool operator==(const Matrix& other) {
        if(height() != other.width() || width() != other.width()) {
            return false;
        }
        for (size_t i = 0; i < width(); ++i) {
            for (size_t j = 0; j < height(); ++j) {
                if(*this[i][j] != *other[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

};


#endif //METNUM_TP2_BASEMATRIX_H
