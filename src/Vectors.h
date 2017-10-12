#ifndef METNUM_TP2_VECTORS_H
#define METNUM_TP2_VECTORS_H

#ifndef NDEBUG
#define NDEBUG
#endif

#include <vector>
#include <cassert>
#include <cmath>

using std::vector;

namespace Vectors {

    template<typename T, typename S>
    vector<S> convert(const vector<T>& orig) {
        return vector<S>(orig.begin(), orig.end());
    }

    template<typename T>
    vector<T> subtract(const vector<T> &a, const vector<T> &b) {
        vector<T> c(a);
        for (size_t i = 0; i < c.size(); ++i) {
            c[i] -= b[i];
        }
        return c;
    }

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
