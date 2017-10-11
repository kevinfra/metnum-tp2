#ifndef METNUM_TP2_POWER_H
#define METNUM_TP2_POWER_H

#include "matrix/FullMatrix.h"

/**
 * Approximates the dominant eigenvalue and corresponding eigenvector of a given matrix
 *
 * @param B the input matrix
 * @param v the output eigenvector
 * @param delta the maximum acceptable delta
 * @param iterations the maximum iterations
 * @throw runtime_error if the method does not converge in the given iterations
 * @return the dominant eigenvalue
 */
double power_method(const MatrixRef<double> B, vector<double> &v, double delta, unsigned long iterations);

MatrixRef<double> deflate(const MatrixRef<double> A, const vector<double> v, const double l);



#endif //METNUM_TP2_POWER_H
