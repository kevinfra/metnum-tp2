#ifndef METNUM_TP2_KNNPCAMACHINE_H
#define METNUM_TP2_KNNPCAMACHINE_H

#include <iostream>
#include "Machine.h"
#include "../knn.h"
#include "../pca.h"
#include "../benchmark/benchmark.h"

#define BENCH_FILE_PCA "bench-pca.csv"
#define BENCH_FILE_PCA_KNN "bench-pcaknn.csv"

class KnnPcaMachine : public Machine {
public:
    KnnPcaMachine(unsigned int k, unsigned int alfa) : k(k), alfa(alfa) {}

    virtual void train(const TrainSet<Pixel> &trainSet) {
        // do PCA on train set, apply base change
        vector<unsigned char> digits;

        MatrixRef<double> trainM = convertTrainSet(trainSet, digits);

        std::cout << "Calculating principal components...  \r" << std::flush;
        INIT_BENCH(BENCH_FILE_PCA);
        START_BENCH;
        baseChangeMatrix =
                alfa != 0 ? pca(trainM, alfa)
                          : pca(trainM);
        END_BENCH(BENCH_FILE_PCA);

        std::cout << "Applying base changes...         \r" << std::flush;
        trainM->inplaceTranspose();
        trainM = baseChangeMatrix->dotProduct(*trainM);
        trainM->inplaceTranspose();

        buildTrainedSet(digits, trainM);
    }

    virtual vector<unsigned char> guess(const TestSet<Pixel> &testSet) {
        vector<unsigned char> results;
        INIT_BENCH(BENCH_FILE_PCA_KNN) << ",guess";
        for (auto testCaseIt = testSet.begin(); testCaseIt != testSet.end() ; testCaseIt++) {
            vector<double> testCase = Vectors::convert<Pixel,double>(*testCaseIt);
            START_BENCH;
            testCase = baseChangeMatrix->dotProduct(testCase);
            unsigned char res =
                    k != 0 ? kNN<double>(testCase, trainSet, k)
                           : kNN<double>(testCase, trainSet);
            END_BENCH(BENCH_FILE_PCA_KNN) << "," << +res;
            results.push_back(res);
        }
        return results;
    }

    virtual vector<unsigned char> guessK(const TestSet<Pixel> &testSet, unsigned int kp) {
        vector<unsigned char> results;
        INIT_BENCH(BENCH_FILE_PCA_KNN) << ",guess";
        for (auto testCaseIt = testSet.begin(); testCaseIt != testSet.end() ; testCaseIt++) {
            vector<double> testCase = Vectors::convert<Pixel,double>(*testCaseIt);
            START_BENCH;
            testCase = baseChangeMatrix->dotProduct(testCase);
            unsigned char res =
                    kp != 0 ? kNN<double>(testCase, trainSet, kp)
                           : kNN<double>(testCase, trainSet);
            END_BENCH(BENCH_FILE_PCA_KNN) << "," << +res;
            results.push_back(res);
        }
        return results;
    }

private:
    MatrixRef<double> baseChangeMatrix;
    TrainSet<double> trainSet;
    unsigned int k;
    unsigned int alfa;

    MatrixRef<double> convertTrainSet(const TrainSet<Pixel> &original, vector<unsigned char> &digits) {
        TestSet<double> set(original.size());
        digits.resize(original.size());
        for (size_t i = 0; i < original.size(); ++i) {
            set[i] = Vectors::convert<Pixel, double>(original[i].img);
            digits[i] = original[i].digit;
        }
        return getTrainMatrix(set);
    }

    MatrixRef<double> getTrainMatrix(const TestSet<double> &X) {
        MatrixRef<double> m = FullMatrix<double>::create(X.size(), IMG_SIZE);
        for (size_t i = 0; i < X.size(); ++i) {
            for (size_t j = 0; j < IMG_SIZE; ++j) {
                (*m)[i][j] = X[i][j];
            }
        }
        return m;
    }

    void buildTrainedSet(const vector<unsigned char> &digits, const ConstMatrixRef<double> &newSet) {
        trainSet.resize(digits.size());
        for (size_t i = 0; i < digits.size(); ++i) {
            trainSet[i] = {(*newSet)[i], digits[i]};
        }
    }

};


#endif //METNUM_TP2_KNNPCAMACHINE_H
