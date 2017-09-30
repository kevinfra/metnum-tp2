#ifndef METNUM_TP2_BASEMATRIX_H
#define METNUM_TP2_BASEMATRIX_H

#include <cstddef>

template < typename T >
class BaseMatrix {
public:
    class BaseUnit {
    public:
        BaseUnit(size_t r, size_t c, BaseMatrix& mx) : row(r), col(c), matrix(mx) {}

        virtual T operator*() const {
            return matrix.get(row, col);
        }

        virtual void operator=(const T& other) {
            matrix.set(row, col, other);
        }


    private:
        size_t row;
        size_t col;
        BaseMatrix& matrix;
    };

    class ConstUnit {
    public:
        ConstUnit(size_t r, size_t c, const BaseMatrix& mx) : row(r), col(c), matrix(mx) {}

        virtual T operator*() const {
            return matrix.get(row, col);
        }

    private:
        size_t row;
        size_t col;
        const BaseMatrix& matrix;
    };

    class BaseRow {
    public:
        BaseRow(size_t pos, BaseMatrix& mx) : row(pos), matrix(mx) {}

        BaseUnit operator[](size_t pos) const {
            return BaseUnit(row, pos, matrix);
        }

        size_t size() const {
            return matrix.width();
        }

    private:

        size_t row;
        BaseMatrix& matrix;
    };

    class ConstRow {
    public:
        ConstRow(size_t pos, const BaseMatrix& mx) : row(pos), matrix(mx) {}

        ConstUnit operator[](size_t pos) const {
            return ConstUnit(row, pos, matrix);
        }

        size_t size() const {
            return matrix.width();
        }

    private:

        size_t row;
        const BaseMatrix& matrix;
    };

    BaseMatrix() {}

    BaseMatrix(const BaseMatrix& other);

    virtual ~BaseMatrix() {}

    virtual BaseRow operator[](size_t pos) {
        return BaseRow(pos, *this);
    }

    virtual ConstRow operator[](size_t pos) const {
        return ConstRow(pos, *this);
    }

    virtual T get(size_t row, size_t col) const = 0;

    virtual void set(size_t row, size_t col, const T& val) = 0;

    virtual size_t width() const = 0;

    virtual size_t height() const = 0;

    bool operator==(const BaseMatrix& other) {
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
