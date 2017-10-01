#include "Methods.h"
#include "matrix/matrix.h"

namespace Methods {

    double power_method(matrix<double> &B, row<double> &v, double delta, unsigned long iterations) {
        double old_lambda = INFINITY;
        row<double> bv = Matrix::dotProductWithVector(B, v);
        for (unsigned long i = 0; i < iterations; i++) {
            // v = Bv/|Bv|
            double norm = Matrix::vectorNorm(bv);
            for (size_t vi = 0; vi < v.size(); ++vi){
                v[vi] = bv[vi] / norm;
            }
            bv = Matrix::dotProductWithVector(B, v);
            double lambda = Matrix::productRowCol(v, bv) / Matrix::vectorNormSquared(v);//v'Bv/v'v
            if (abs(lambda - old_lambda) < delta) { //REVISAR CONDICION DE PARADA
                return lambda;
            }
            old_lambda = lambda;
        }
        assert(false); //Si no converge en la cantidad de iteraciones rompemos todo:
    }
}
