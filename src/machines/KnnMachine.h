#ifndef METNUM_TP2_KNNMACHINE_H
#define METNUM_TP2_KNNMACHINE_H

#include <iostream>
#include "Machine.h"
#include "../io/MatrixIterator.h"
#include "../knn.h"
#include "../benchmark/benchmark.h"

#define K 10
#define BENCH_FILE_KNN "bench-knn.csv"

class KnnMachine : public Machine {
public:
    virtual void train(const TrainSet<Pixel> &trainSet) {
        // data is already formatted, just load it
        this->trainSet = trainSet;
    }

    virtual vector<unsigned char> guess(const TestSet<Pixel> &testSet) {
        vector<unsigned char> results;
        INIT_BENCH(BENCH_FILE_KNN) << ",guess";
        for (auto testCaseIt = testSet.begin(); testCaseIt != testSet.end() ; testCaseIt++) {
            START_BENCH;
            unsigned char res = kNN<unsigned char>(K, *testCaseIt, trainSet);
            END_BENCH(BENCH_FILE_KNN) << "," << +res;
            results.push_back(res);
        }
        return results;
    }

private:
    TrainSet<unsigned char> trainSet;

};


#endif //METNUM_TP2_KNNMACHINE_H
