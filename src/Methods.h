#ifndef METNUM_TP2_METHODS_H
#define METNUM_TP2_METHODS_H

#include "matrix/FullMatrix.h"

namespace Methods {

    double power_method(const Matrix<double> &B, row<double> &v, double delta, unsigned long iterations);

}


#endif //METNUM_TP2_METHODS_H
