#include <cstdlib>
#include "Methods.h"

namespace Methods {

    double power_method(const Matrix<double> &B, row<double> &v, double delta, unsigned long iterations) {
        for (size_t vi = 0; vi < v.size(); ++vi){
            v[vi] = (double)rand(); //TODO: ver el rango de los numeros aleatorios
        }
        double old_lambda = INFINITY;
        row<double> bv = B.dotProduct(v);
        for (unsigned long i = 0; i < iterations; i++) {
            // v = Bv/|Bv|
            double norm = Vectors::twoNorm(bv);
            for (size_t vi = 0; vi < v.size(); ++vi){
                v[vi] = bv[vi] / norm;
            }
            bv = B.dotProduct(v);
            double lambda = Vectors::innerProduct(v, bv) / Vectors::twoNormSquared(v);//v'Bv/v'v
            if (abs(lambda - old_lambda) < delta) { //REVISAR CONDICION DE PARADA
                return lambda;
            }
            old_lambda = lambda;
        }
        assert(false); //Si no converge en la cantidad de iteraciones rompemos todo:
    }
}
