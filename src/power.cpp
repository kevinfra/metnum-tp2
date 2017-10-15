#include <cstdlib>
#include "power.h"

MatrixRef<double> outerProduct(const vector<double> &a, const vector<double> &b) {
    MatrixRef<double> mat = FullMatrix<double>::create(a.size(), b.size());
    for (size_t i = 0; i < a.size(); i++)
        for (size_t j = 0; j < b.size(); j++)
            (*mat)[i][j] = a[i] * b[j];
    return mat;
}

double power_method(const ConstMatrixRef<double> &B, vector<double> &v, double delta) {
    v.resize(B->width());
    for (size_t vi = 0; vi < v.size(); ++vi) {
        // TODO: ver el rango de los numeros aleatorios
        // also, los numeros son todos enteros, es eso correcto? o queremos doubles random?
        v[vi] = (double)rand();
    }
    vector<double> bv = B->dotProduct(v);
    double oldnorm = INFINITY;
    double diff = INFINITY;
    double lambda = INFINITY;
    for (unsigned long i = 0; i < POWER_MAX_ITERS && diff > delta; i++) {
        // v = Bv/|Bv|
        double norm = Vectors::twoNorm(bv);
        for (size_t vi = 0; vi < v.size(); ++vi){
            v[vi] = bv[vi] / norm;
        }
        bv = B->dotProduct(v);
        // lambda = v'Bv/v'v
        lambda = Vectors::innerProduct(v, bv) / Vectors::twoNormSquared(v);
        diff = std::abs(oldnorm - norm);
        oldnorm = norm;
    }
    return lambda;
}

MatrixRef<double> deflate(const ConstMatrixRef<double> &A, const vector<double> v, const double l) {
    return (*A) - *outerProduct(v, v)->dotProduct(l);
}
