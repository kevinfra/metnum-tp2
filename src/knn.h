#ifndef METNUM_TP2_KNN_H
#define METNUM_TP2_KNN_H

#include <vector>
#include <assert.h>
#include <limits>
#include "matrix/FullMatrix.h"
#include "math.h"

int kNN(int k, const BaseMatrix<double> &unknownNumber, row< BaseMatrix<double> > &knownNumbers);

#endif //METNUM_TP2_KNN_H
