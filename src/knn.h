#ifndef METNUM_TP2_KNN_H
#define METNUM_TP2_KNN_H

#include <limits>
#include "math.h"
#include "io/IO.h"
#include "SortedKList.h"

template < typename T >
struct Neighbour {
    TrainCase<T> trainUnit;
    double distance;

    bool operator<(const Neighbour& other) const {
        return distance < other.distance;
    }
};

template < typename T >
unsigned char kNN(size_t k, const vector<T> unknownNumber, const vector<TrainCase<T>> &knownNumbers) {
    // Invariante: el valor en la pos i de minNorms corresponde a la norma de ||unkownNumber - knownNumber||2
    // donde knownNumber es nn[i]
    // Además, validKnownNumbers indica si en la pos i de nn hay una matriz valida.
    SortedKList<Neighbour<T>> nearest(k);

    for (auto it = knownNumbers.begin(); it != knownNumbers.end(); ++it) {
        TrainCase<T> trainCase = *it;
        vector<T> diff = Vectors::subtract(trainCase.img, unknownNumber);
        double twoNorm = Vectors::twoNorm(diff);

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
    return max;
}


#endif //METNUM_TP2_KNN_H
