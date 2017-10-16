#ifndef METNUM_TP2_MATRIX_H
#define METNUM_TP2_MATRIX_H

#include <cstddef>
#include <cmath>
#include <memory>
#include "../Vectors.h"

template < typename T >
class Matrix;

template < typename T >
using MatrixRef = std::shared_ptr<Matrix<T>>;

template < typename T >
using ConstMatrixRef = std::shared_ptr<const Matrix<T>>;

template < typename T >
class Matrix {
public:
    class Unit {
    public:
        Unit(size_t r, size_t c, Matrix& mx) : row(r), col(c), matrix(mx) {}

        operator T() const {
            return matrix.get(row, col);
        }

        void operator=(const Unit& other) {
            *this = T(other);
        }

        void operator=(const T& other) {
            matrix.set(row, col, other);
        }

    private:
        size_t row;
        size_t col;
        Matrix& matrix;
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

        operator vector<T>() const {
            vector<T> v(size(), static_cast<T>(0));
            for (size_t i = 0; i < size(); ++i) {
                v[i] = matrix.get(row, i);
            }
            return v;
        }

    private:

        size_t row;
        Matrix& matrix;
    };

    class ConstRow {
    public:
        ConstRow(size_t pos, const Matrix& mx) : row(pos), matrix(mx) {}

        T operator[](size_t pos) const {
            return get(pos);
        }

        size_t size() const {
            return matrix.width();
        }

        operator vector<T>() const {
            vector<T> v(size(), static_cast<T>(0));
            for (size_t i = 0; i < size(); ++i) {
                v[i] = get(i);
            }
            return v;
        }

    private:

        T get(size_t pos) const {
            return matrix.get(row, pos);
        }

        size_t row;
        const Matrix& matrix;
    };

    virtual ~Matrix() {}

    virtual Row operator[](size_t pos) {
        return Row(pos, *this);
    }

    virtual ConstRow operator[](size_t pos) const {
        return ConstRow(pos, *this);
    }

    virtual MatrixRef<T> makeNew(size_t height, size_t width) const = 0;

    // common operations

    virtual T get(size_t row, size_t col) const {
        if(transposed) {
            return internal_get(col, row);
        } else {
            return internal_get(row, col);
        }
    }

    virtual void set(size_t row, size_t col, const T& val) {
        if(transposed) {
            internal_set(col, row, val);
        } else {
            internal_set(row, col, val);
        }
    }

    size_t width() const {
        if(transposed) {
            return internal_height();
        } else {
            return internal_width();
        }
    }

    size_t height() const {
        if(transposed) {
            return internal_width();
        } else {
            return internal_height();
        }
    }

    MatrixRef<T> makeNew() const {
        return makeNew(height(), width());
    }

    MatrixRef<T> copy() const {
        MatrixRef<T> copy = makeNew();
        copy->copyFrom(*this);
        return copy;
    }

    void copyFrom(const Matrix& other) {
        transposed = other.transposed;
        for (size_t i = 0; i < other.height(); ++i) {
            for (size_t j = 0; j < other.width(); ++j) {
                set(i,j, other.get(i,j));
            }
        }
    }

    virtual MatrixRef<T> dotProduct(const T &a) const {
        MatrixRef<T> result = makeNew();

        for (size_t i = 0; i < height(); i++)
            for (size_t j = 0; j < width(); j++)
                (*result)[i][j] = get(i,j) * a;

        return result;
    }

    virtual MatrixRef<T> dotProduct(const Matrix &b) const {
        MatrixRef<T> c = makeNew(height(), b.width());

        // matrices must be non-empty
        assert(height() > 0 && width() > 0);
        assert(b.height() > 0 && b.width() > 0);
        // input dimensions must match
        assert(width() == b.height());
        // output dimensions must match
        assert(c->height() == height());
        assert(c->width() == b.width());

        for (size_t i = 0; i < c->height(); ++i) {
            for (size_t j = 0; j < c->width(); ++j) {
                T val = 0;
                for (size_t k = 0; k < b.height(); ++k) {
                     val += get(i,k) * b.get(k, j);
                }
                (*c)[i][j] = val;
            }
        }
        return c;
    }

    virtual vector<T> dotProduct(const vector<T> &b) const {
        vector<T> c(height(), 0);
        // matrices must be non-empty
        assert(height() > 0 && width() > 0);
        assert(b.size() > 0);
        // input dimensions must match
        assert(width() == b.size());
        // output dimensions must match
        assert(c.size() == height());

        for (size_t i = 0; i < height(); ++i) {
            for (size_t j = 0; j < width(); ++j) {
                c[i] += get(i,j) * b[j];
            }
        }
        return c;
    }

    virtual MatrixRef<T> operator+(const Matrix &b) const {
        MatrixRef<T> c = makeNew();

        // matrices must be non-empty
        assert(height() > 0 && width() > 0);
        // input dimensions must match
        assert(height() == b.height());
        assert(width() == b.width());
        // output dimensions must match
        assert(height() == c->height());
        assert(width() == c->width());

        for (size_t i = 0; i < height(); ++i) {
            for (size_t j = 0; j < width(); ++j) {
                (*c)[i][j] = get(i,j) + b.get(i,j);
            }
        }
        return c;
    }

    virtual MatrixRef<T> operator-(const Matrix &b) const {
        MatrixRef<T> c = makeNew();

        // matrices must be non-empty
        assert(height() > 0 && width() > 0);
        // input dimensions must match
        assert(height() == b.height());
        assert(width() == b.width());
        // output dimensions must match
        assert(height() == c->height());
        assert(width() == c->width());

        for (size_t i = 0; i < height(); ++i) {
            for (size_t j = 0; j < width(); ++j) {
                (*c)[i][j] = get(i,j) - b.get(i,j);
            }
        }
        return c;
    }

    virtual MatrixRef<T> operator*(const T &a) const {
        MatrixRef<T> result = makeNew();

        for (size_t i = 0; i < height(); i++)
            for (size_t j = 0; j < width(); j++)
                (*result)[i][j] = get(i,j) * a;

        return result;
    }

    virtual void inplaceTranspose() {
        transposed = !transposed;
    }

    virtual MatrixRef<T> transpose() const {
        MatrixRef<T> t = makeNew(width(), height());
        // matrix must be non-empty
        assert(height() > 0 && width() > 0);
        // output dimensions must match
        assert(height() == t->width());
        assert(width() == t->height());

        for (size_t i = 0; i < height(); ++i) {
            for (size_t j = 0; j < width(); ++j) {
                (*t)[j][i] = get(i,j);
            }
        }
        return t;
    }

    virtual MatrixRef<T> transposedProduct() const {
        MatrixRef<T> t = makeNew(height(), height());
        // matrix must be non-empty
        assert(height() > 0 && width() > 0);
        // output dimensions must match
        assert(height() == t->width());
        assert(height() == t->height());

        for (size_t i = 0; i < height(); ++i) {
            for (size_t j = 0; j <= i; ++j) {
                T val = static_cast<T>(0);
                for (size_t k = 0; k < width(); ++k) {
                    val += get(i,k) * get(j,k);
                }
                (*t)[i][j] = val;
                if (i != j) {
                    (*t)[j][i] = val;
                }
            }
        }
        return t;
    }

    virtual double infinityNorm() const {
        assert(height() > 0 && width() > 0);
        double result = get(0,0);
        for (size_t i = 0; i < height(); ++i) {
            for (size_t j = 0; j < width(); ++j) {
                if (result < get(i,j)) {
                    result = get(i,j);
                }
            }
        }
        return result;
    }

    virtual double twoNorm() const {
        double result = 0;
        for (size_t i = 0; i < height(); ++i) {
            double c = 0.0;
            for (size_t j = 0; j < width(); ++j) {
                // Super Kahan2!!
                double y = std::pow(get(i,j), 2) - c;
                double t = result + y;
                c = (t - result) - y;
                result = t;
            }
        }
        return sqrt(result);
    }

    virtual double singleNorm() const {
        double result = 0;
        for (size_t i = 0; i < height(); ++i) {
            double c = 0.0;
            for (size_t j = 0; j < width(); ++j) {
                // Super Kahan!!
                double y = double(get(i,j)) - c;
                double t = result + y;
                c = (t - result) - y;
                result = t;
            }
        }
        return result;
    }

    virtual bool isSquared() const {
        return height() == width();
    }

    virtual bool isDiagonal() const {
        if(!isSquared()) {
            return false;
        }
        for (size_t i = 0; i < height(); ++i) {
            for (size_t j = 0; j < width(); ++j) {
                if (i != j && get(i,j) != 0) {
                    return false;
                }
            }
        }
        return true;
    }

    virtual bool isLowerTriangular() const {
        if(!isSquared()) {
            return false;
        }
        for (size_t i = 0; i < height(); ++i) {
            for (size_t j = i + 1; j < width(); ++j) {
                if (get(i,j) != 0) {
                    return false;
                }
            }
        }
        return true;
    }

    virtual bool isUpperTriangular() const {
        if(!isSquared()) {
            return false;
        }
        for (size_t i = 0; i < height(); ++i) {
            for (size_t j = 0; j < i; ++j) {
                if (get(i,j) != 0) {
                    return false;
                }
            }
        }
        return true;
    }

    virtual bool isSymmetric() const {
        if(!isSquared()) {
            return false;
        }
        for (size_t i = 0; i < height(); ++i) {
            for (size_t j = 0; j < i; ++j) {
                if (get(i,j) != get(j,i)) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator==(const Matrix& other) const {
        if(height() != other.height() || width() != other.width()) {
            return false;
        }
        for (size_t i = 0; i < height(); ++i) {
            for (size_t j = 0; j < width(); ++j) {
                if(get(i,j) != other.get(i,j)) {
                    return false;
                }
            }
        }
        return true;
    }

    // Special matrix system solutions

    // This should solve Ax=b and return x for lower triangular squared systems
    static vector<T> solveLowerTriangularSquaredSystem(const Matrix &A, const vector<T> &b) {
        assert(A.isLowerTriangular());

        size_t solution_size = A.height();
        vector <T> solution(solution_size, 0);
        for (size_t i = 0; i < solution_size; ++i) {
            T sumOfRowI = 0;
            T c = 0.0;
            for (size_t j = 0; j < i; ++j) {
                T y = (A.get(i,j) * solution[j]) - c;
                T t = sumOfRowI + y;
                c = (t - sumOfRowI) - y;
                sumOfRowI = t;
            }
            solution[i] = (b[i] - sumOfRowI) / A.get(i,i);
        }

        return solution;
    }

    // This should solve Ax=b and return x for upper triangular squared systems
    static vector<T> solveUpperTriangularSquaredSystem(const Matrix &A, const vector<T> &b) {
        assert(A.isUpperTriangular());

        size_t solution_size = A.height();
        vector<T> solution(solution_size, 0);
        for (ssize_t i = solution_size - 1; i >= 0; --i) {
            T sumOfRowI = 0;
            T c = 0.0;
            for (ssize_t j = solution_size - 1; j > i; --j) {
                T y = (A.get(i,j) * solution[j]) - c;
                T t = sumOfRowI + y;
                c = (t - sumOfRowI) - y;
                sumOfRowI = t;
            }
            solution[i] = (b[i] - sumOfRowI) / A.get(i,i);
        }

        return solution;
    }

    /*
     * This should solve LUx=b and return x for LU systems
     * LUx = b
     * 1) Ly = b
     * 2) Ux = y
     */
    static vector<T> solveLUSystem(const Matrix &L, const Matrix &U, const vector<T> &b) {
        vector<T> y = solveLowerTriangularSquaredSystem(L, b);
        vector<T> x = solveUpperTriangularSquaredSystem(U, y);
        return x;
    }

    /*
     * This should solve PLUx=b and return x for PLU systems
     * LUx = (P**-1) b
     * 1) Ly = (P**-1) b
     * 2) Ux = y
     */
    static vector<T> solvePLUSystem(const Matrix &P, const Matrix &L, const Matrix &U, const vector<T> &b) {
        MatrixRef<T> inverseP = P.transpose();
        vector<T> permutedB = inverseP->dotProduct(b);
        vector<T> x = solveLUSystem(L, U, permutedB);
        return x;
    }

    /*
     * This should solve LL*x=b and return x for Cholesky systems
     * LL*x = b
     * 1) Ly = b
     * 2) L*x = y
     *
     */
    static vector<T> solveCholeskySystem(const Matrix &L, const vector<T> &b) {
        vector<T> y = solveLowerTriangularSquaredSystem(L, b);
        MatrixRef<T> trasposedL = L.transpose();
        vector<T> x = solveUpperTriangularSquaredSystem(*trasposedL, y);
        return x;
    }

protected:
    // subclass-defined core functions
    virtual T internal_get(size_t row, size_t col) const = 0;

    virtual void internal_set(size_t row, size_t col, const T& val) = 0;

    virtual size_t internal_width() const = 0;

    virtual size_t internal_height() const = 0;

private:
    bool transposed = false;
};

#endif //METNUM_TP2_MATRIX_H
