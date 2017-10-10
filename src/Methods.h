#ifndef METNUM_TP2_METHODS_H
#define METNUM_TP2_METHODS_H

#include "matrix/FullMatrix.h"

namespace Methods {

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
    double power_method(const MatrixRef<double> &B, vector<double> &v, double delta, unsigned long iterations);
}



#endif //METNUM_TP2_METHODS_H
