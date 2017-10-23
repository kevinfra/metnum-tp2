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
unsigned char kNN(const vector<T> unknownNumber, const vector<TrainCase<T>> &knownNumbers, unsigned int k = 10) {
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

    // count how many of the k nearest belong to each digit
    size_t count[10] {0};
    // priority is higher if the known digit was closer to the unknown digit
    // helps keep how close digits were after counting, in case of ties
    unsigned int priority[10] {0};
    unsigned int p = 1;

    for (auto it = nearest.begin(); it != nearest.end(); ++it) {
        unsigned char d = it->trainUnit.digit;
        ++count[d];

        priority[d] = p;
        ++p;
    }

    unsigned char max = 0;
    for (unsigned char i = 1; i < 10; ++i) {
        if(count[i] > count[max]) {
            max = i;
        } else if (count[i] == count[max] && priority[i] > priority[max]) {
            max = i;
        }
    }
    return max;
}


#endif //METNUM_TP2_KNN_H
