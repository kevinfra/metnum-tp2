#ifndef METNUM_TP2_KNNMACHINE_H
#define METNUM_TP2_KNNMACHINE_H

#include <iostream>
#include "Machine.h"
#include "../io/MatrixIterator.h"
#include "../knn.h"
#include "../benchmark/benchmark.h"

#define BENCH_FILE_KNN "bench-knn.csv"

class KnnMachine : public Machine {
public:
    KnnMachine(unsigned int k) : k(k) {}

    virtual void train(const TrainSet<Pixel> &trainSet) {
        // data is already formatted, just load it
        this->trainSet = trainSet;
    }

    virtual vector<unsigned char> guess(const TestSet<Pixel> &testSet) {
        vector<unsigned char> results;
        INIT_BENCH(BENCH_FILE_KNN) << ",guess";
        for (auto testCaseIt = testSet.begin(); testCaseIt != testSet.end() ; testCaseIt++) {
            START_BENCH;
            unsigned char res =
                    k > 0 ? kNN<unsigned char>(*testCaseIt, trainSet, k)
                          : kNN<unsigned char>(*testCaseIt, trainSet);
            END_BENCH(BENCH_FILE_KNN) << "," << +res;
            results.push_back(res);
        }
        return results;
    }

    virtual vector<unsigned char> guessK(const TestSet<Pixel> &testSet, unsigned int kp) {
        vector<unsigned char> results;
        INIT_BENCH(BENCH_FILE_KNN) << ",guess";
        for (auto testCaseIt = testSet.begin(); testCaseIt != testSet.end() ; testCaseIt++) {
            START_BENCH;
            unsigned char res =
                    kp > 0 ? kNN<unsigned char>(*testCaseIt, trainSet, kp)
                          : kNN<unsigned char>(*testCaseIt, trainSet);
            END_BENCH(BENCH_FILE_KNN) << "," << +res;
            results.push_back(res);
        }
        return results;
    }

private:
    TrainSet<unsigned char> trainSet;
    unsigned int k;

};


#endif //METNUM_TP2_KNNMACHINE_H
