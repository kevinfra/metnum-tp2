#ifndef METNUM_TP2_KNN_H
#define METNUM_TP2_KNN_H

#include <vector>
#include <assert.h>
#include <limits>
#include "matrix/FullMatrix.h"
#include "math.h"
#include "io/IO.h"
#include "io/TrainSetIterator.h"
#include "SortedKList.h"
#include "benchmark/benchmark.h"

template < typename T >
struct Neighbour {
    TrainCase<T> trainUnit;
    double distance;

    bool operator<(const Neighbour& other) const {
        return distance < other.distance;
    }
};

template < typename T >
//unsigned char kNN(size_t k, const MatrixRef<T> &unknownNumber, TrainSetIterator<T> &knownNumbers) {
unsigned char kNN(size_t k, const MatrixRef<T> &unknownNumber, const vector<TrainCase<T>> &knownNumbers) {
    // Invariante: el valor en la pos i de minNorms corresponde a la norma de ||unkownNumber - knownNumber||2
    // donde knownNumber es nn[i]
    // Además, validKnownNumbers indica si en la pos i de nn hay una matriz valida.
    START_BENCH;
    SortedKList<Neighbour<T>> nearest(k);

    for (auto it = knownNumbers.begin(); it != knownNumbers.end(); ++it) {
        TrainCase<T> trainCase = *it;
        MatrixRef<T> knownNumber = trainCase.img;
        MatrixRef<T> difMatrix = *trainCase.img - *unknownNumber;
        double twoNorm = difMatrix->twoNorm();

        nearest.insertIfNecessary({trainCase, twoNorm});
    }

    size_t count[10] = {0};
    for (auto it = nearest.begin(); it != nearest.end(); ++it) {
        ++count[it->trainUnit.digit];
    }
    unsigned char max = 0;
    for (unsigned char i = 1; i < 10; ++i) {
        if(count[i] > count[max]) {
            max = i;
        }
    }
    END_BENCH("bench-knn.csv") << "," << max;
    return max;
}


#endif //METNUM_TP2_KNN_H
