#ifndef METNUM_TP2_VECTORS_H
#define METNUM_TP2_VECTORS_H

#include <vector>
#include <assert.h>
#include <cmath>

using std::vector;

namespace Vectors {

    template<typename T>
    double innerProduct(const vector<T> &a, const vector<T> &b) {
        double res = 0;
        for (size_t i = 0; i < a.size(); ++i){
            res += a[i] * b[i];
        }
        return res;
    }

    template<typename T>
    double twoNormSquared(const vector<T> &v) {
        return innerProduct(v, v);
    }

    template<typename T>
    double twoNorm(const vector<T> &v) {
        return std::sqrt(twoNormSquared(v));
    }
}

#endif //METNUM_TP2_VECTORS_H
