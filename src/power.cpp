#include <cstdlib>
#include "power.h"

MatrixRef<double> outerProduct(const vector<double> &a, const vector<double> &b) {
    MatrixRef<double> mat = std::make_shared<FullMatrix<double>>(a.size(), b.size());
    for (size_t i = 0; i < a.size(); i++)
        for (size_t j = 0; j < b.size(); j++)
            (*mat)[i][j] = a[i] * b[j];
    return mat;
}

double power_method(const MatrixRef<double> B, vector<double> &v, double delta, unsigned long iterations) {
    v.resize(B->width());
    for (size_t vi = 0; vi < v.size(); ++vi) {
        // TODO: ver el rango de los numeros aleatorios
        // also, los numeros son todos enteros, es eso correcto? o queremos doubles random?
        v[vi] = (double)rand();
    }
    double old_lambda = INFINITY;
    vector<double> bv = B->dotProduct(v);
    double lambda = old_lambda;
    for (unsigned long i = 0; i < iterations; i++) {
        // v = Bv/|Bv|
        double norm = Vectors::twoNorm(bv);
        for (size_t vi = 0; vi < v.size(); ++vi){
            v[vi] = bv[vi] / norm;
        }
        bv = B->dotProduct(v);
        // lambda = v'Bv/v'v
        lambda = Vectors::innerProduct(v, bv) / Vectors::twoNormSquared(v);
        if (std::abs(lambda - old_lambda) < delta) {
            // REVISAR CONDICION DE PARADA
            //return lambda;
            break;
        }
        old_lambda = lambda;
    }
    return lambda;
    //throw std::runtime_error("Power method did not converge!"); //Si no converge en la cantidad de iteraciones rompemos todo
}

MatrixRef<double> deflate(const MatrixRef<double> A, const vector<double> v, const double l) {
    return (*A) - *outerProduct(v, v)->dotProduct(l);
}
