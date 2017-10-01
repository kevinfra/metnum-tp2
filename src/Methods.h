#ifndef METNUM_TP2_METHODS_H
#define METNUM_TP2_METHODS_H

#include "matrix/FullMatrix.h"

namespace Methods {

    double power_method(FullMatrix<double>& B, double delta, unsigned long iterations);

};


#endif //METNUM_TP2_METHODS_H
