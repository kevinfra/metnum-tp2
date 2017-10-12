#ifndef METNUM_TP2_KNNPCAMACHINE_H
#define METNUM_TP2_KNNPCAMACHINE_H

#include <iostream>
#include "Machine.h"
#include "../knn.h"
#include "../pca.h"
#include "../benchmark/benchmark.h"

#define PCA_K 10
#define ALPHA 100
#define BENCH_FILE_PCA "bench-pca.csv"

class KnnPcaMachine : public Machine {
public:
    virtual void train(const TrainSet<Pixel> &trainSet) {
        // do PCA on train set, apply base change
        TrainSet<double> originalTrainSet = convertTrainSet(trainSet);

        MatrixRef<double> trainM = getTrainMatrix(originalTrainSet);

        std::cout << "Calculating principal components...  \r" << std::flush;
        baseChangeMatrix = pca(trainM, ALPHA);

        std::cout << "Applying base changes...         \r" << std::flush;
        trainM->inplaceTranspose();
        trainM = baseChangeMatrix->dotProduct(*trainM);
        trainM->inplaceTranspose();
        this->trainSet = buildTrainedSet(originalTrainSet, trainM);
    }

    virtual vector<unsigned char> guess(const TestSet<Pixel> &testSet) {
        vector<unsigned char> results;
        INIT_BENCH(BENCH_FILE_PCA);
        for (auto testCaseIt = testSet.begin(); testCaseIt != testSet.end() ; testCaseIt++) {
            vector<double> testCase = Vectors::convert<Pixel,double>(*testCaseIt);
            START_BENCH;
            testCase = baseChangeMatrix->dotProduct(testCase);
            unsigned char res = kNN<double>(PCA_K, testCase, trainSet);
            END_BENCH(BENCH_FILE_PCA) << "," << +res;
            results.push_back(res);
        }
        return results;
    }

private:
    MatrixRef<double> baseChangeMatrix;
    TrainSet<double> trainSet;

    TrainSet<double> convertTrainSet(const TrainSet<Pixel> &original) {
        TrainSet<double> set;
        for (auto it = original.begin(); it != original.end(); ++it) {
            set.push_back({Vectors::convert<Pixel, double>(it->img), it->digit});
        }
        return set;
    }

    MatrixRef<double> getTrainMatrix(const TrainSet<double> &X) {
        MatrixRef<double> m = FullMatrix<double>::create(X.size(), IMG_SIZE);
        for (size_t i = 0; i < X.size(); ++i) {
            for (size_t j = 0; j < IMG_SIZE; ++j) {
                (*m)[i][j] = X[i].img[j];
            }
        }
        return m;
    }

    TrainSet<double> buildTrainedSet(const TrainSet<double> &originalSet, const MatrixRef<double> newSet) {
        TrainSet<double> set(originalSet);
        for (size_t i = 0; i < set.size(); ++i) {
            set[i].img = (*newSet)[i];
        }
        return set;
    }

};


#endif //METNUM_TP2_KNNPCAMACHINE_H
