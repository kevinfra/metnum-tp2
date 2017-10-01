#include "Methods.h"
#include "matrix/matrix.h"

namespace Methods {

    double power_method(matrix<double> &B, row<double> &v, double delta, unsigned long iterations) {
        for (unsigned long i = 0; i < iterations; i++) {
            // v = Bv/|Bv|
            v = Matrix::dotProductWithVector(B, v);
            double norm = Matrix::vectorNorm(v); // v /= norm(v)
            for (size_t vi = 0; vi < v.size(); ++vi){
                v[vi] /= norm;
            }
            //Aca podemos hacer condicion de parada por delta
        } //Esto se va llamar con un vector v aleatorio, y podia ser que de mal no recuerdo como analizarlo
        row<double> bv = Matrix::dotProductWithVector(B, v);
        return Matrix::productRowCol(v, bv) / Matrix::vectorNormSquared(v);
    }
}
